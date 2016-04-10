#include "Blueprint/Parser/Parser.hpp"

#include "Blueprint/Database/Database.hpp"
#include "Blueprint/Database/SqliteApi.hpp"
#include "Blueprint/Parser/Clang/Index.hpp"
#include "Blueprint/Parser/Visitors/NamespaceVisitor.hpp"
#include "Blueprint/Parser/CommandLineArguments.hpp"
#include "Blueprint/Reflection/Visitors/TypeEnumerator.hpp"
#include "Blueprint/Reflection/ClassType.hpp"
#include "Blueprint/Reflection/EnumType.hpp"
#include "Blueprint/Reflection/TypeRegistry.hpp"
#include "Blueprint/Utilities/JsonImporter.hpp"
#include "Blueprint/Utilities/ScopeTimer.hpp"
#include "Blueprint/Utilities/WorkingDirectory.hpp"
#include "Blueprint/Workspace/Workspace.hpp"

namespace blueprint
{
    namespace internal
    {
        void DisplayDiagnostics(const clang::TranslationUnit& translationUnit)
        {
            static auto pragmaOnceInMainFile = "warning: #pragma once in main file";
            static auto options = clang::Diagnostic::GetDefaultOptions();

            for (auto& diagnostic : translationUnit.GetDiagnostics())
            {
                auto message = diagnostic.Format(options).Get();

                if (message.find(pragmaOnceInMainFile) != std::string::npos)
                {
                    continue;
                }

                std::cout << message << std::endl;
            }
        }

        void EnsureDirectoryExists(const filesystem::path& directory)
        {
            if (!directory.is_directory())
            {
                filesystem::create_directory(directory);
            }
        }

        bool IsSourceFile(const filesystem::path& file)
        {
            auto extension = file.extension();

            return extension == "c"
                || extension == "cc"
                || extension == "cpp";
        }

        bool IsHeaderFile(const filesystem::path& file)
        {
            auto extension = file.extension();

            return extension == "h"
                || extension == "hh"
                || extension == "hpp";
        }

        void SaveTypes(const reflection::TypeEnumerator& enumerator, const filesystem::path& outputDir)
        {
            std::cout << std::endl;
            std::cout << "> saving database :" << std::endl;

            ScopeTimer timer([](double time) {
                std::cout << time << "s" << std::endl;
            });

            sqlite3pp::database db((outputDir / "registry.db").str().c_str());
            database::Database database(db);

            auto& classes = enumerator.GetClasses();
            auto& enums = enumerator.GetEnums();

            std::vector<const reflection::Type*> types;
            types.reserve(classes.size() + enums.size());

            types.insert(types.end(), classes.begin(), classes.end());
            types.insert(types.end(), enums.begin(), enums.end());

            database.Initialize();
            database.InsertTypes(types);
        }

        void ListTypes(const reflection::TypeEnumerator& enumerator)
        {
            std::cout << std::endl;
            std::cout << "> listing types :" << std::endl;

            ScopeTimer timer([](double time) {
                std::cout << "> " << time << "s" << std::endl;
            });

            auto sorter = [](auto lhs, auto rhs)
            {
                return lhs->GetFullName() < rhs->GetFullName();
            };

            auto classes = enumerator.GetClasses();
            auto enums = enumerator.GetEnums();

            if (!classes.empty())
            {
                std::cout << ">> classes : (" << classes.size() << ")" << std::endl;

                std::sort(classes.begin(), classes.end(), sorter);

                for (auto type : classes)
                {
                    std::cout << ">>> " << type->GetFullName() << std::endl;
                }
            }

            if (!enums.empty())
            {
                std::cout << ">> enum : (" << enums.size() << ")" << std::endl;

                std::sort(enums.begin(), enums.end(), sorter);

                for (auto type : enums)
                {
                    std::cout << ">>> " << type->GetFullName() << std::endl;
                }
            }
        }
    }

    class Parser::Impl
    {
    public:
        const clang::Index& GetIndex() const
        {
            return index_;
        }

        reflection::TypeRegistry& GetTypeRegistry()
        {
            return typeRegistry_;
        }

    private:
        clang::Index index_;

        reflection::TypeRegistry typeRegistry_;
    };

    struct Parser::FileContext
    {
        const Configuration* config{nullptr};

        filesystem::path filePath;

        CommandLineArguments arguments;

        bool saveDependencies{true};
        bool includePrecompiled{false};
        bool save{false};
    };

    Parser::Parser()
        : pimpl_(new Impl())
    {}

    Parser::~Parser() = default;

    bool Parser::ParseWorkspace(const filesystem::path& filePath)
    {
        if (filePath.str().empty())
        {
            std::cout << "invalid workspace filename" << std::endl;
            return false;
        }

        WorkingDirectory::SetCurrent(filePath.make_absolute().parent_path().str());
        std::cout << "{ cwd : " << WorkingDirectory::GetCurrent() << " }" << std::endl;

        internal::EnsureDirectoryExists(outputDirectory_);

        auto workspace = JsonImporter::ImportWorkspace(filePath.filename());
        return ParseWorkspace(workspace.get());
    }

    bool Parser::ParseWorkspace(const Workspace* workspace)
    {
        if (workspace == nullptr)
        {
            std::cout << "invalid workspace" << std::endl;
            return false;
        }

        std::cout << "{ libclang index version " << CINDEX_VERSION_STRING << " }" << std::endl;
        std::cout << "{ libclang " << clang::String(clang_getClangVersion()).Get() << " }" << std::endl;
        std::cout << std::endl;

        std::cout << "> workspace : " << workspace->GetName() << std::endl;

        {
            ScopeTimer timer([](double time) {
                std::cout << "> " << time << "s" << std::endl;
            });

            auto originalOutput = outputDirectory_;

            for (auto& project : workspace->GetProjects())
            {
                outputDirectory_ = originalOutput / project->GetName();
                internal::EnsureDirectoryExists(outputDirectory_);

                if (!ParseProject(project.get()))
                {
                    return false;
                }
            }

            outputDirectory_ = originalOutput;
        }

        reflection::TypeEnumerator enumerator;
        pimpl_->GetTypeRegistry().Accept(enumerator);

        if (listTypes_)
        {
            internal::ListTypes(enumerator);
        }

        internal::SaveTypes(enumerator, outputDirectory_);

        return true;
    }

    bool Parser::ParseProject(const filesystem::path& filePath)
    {
        if (filePath.str().empty())
        {
            std::cout << "invalid project filename" << std::endl;
            return false;
        }

        auto project = JsonImporter::ImportProject(filePath);
        return ParseProject(project.get());
    }

    bool Parser::ParseProject(const Project* project)
    {
        if (project == nullptr)
        {
            std::cout << "invalid project" << std::endl;
            return false;
        }

        std::cout << ">> project  : " << project->GetName() << std::endl;

        const Configuration* config = nullptr;

        if (!project->GetConfigurations().empty())
        {
            config = project->GetConfigurations()[0].get();
        }

        if (config == nullptr)
        {
            std::cout << "invalid config" << std::endl;
            return false;
        }

        CommandLineArguments arguments;
        arguments.ImportConfig(config);
        arguments.Add("-std=c++14"); // Language standard to compile for
        arguments.Add("-w");         // Suppress all warnings

        if (verbose_)
        {
            arguments.Add("-v"); // Show commands to run and use verbose output
        }

        {
            ScopeTimer timer([](double time) {
                std::cout << ">> " << time << "s" << std::endl;
            });

            if (config->HasPrecompiledHeader())
            {
                FileContext context;

                context.config = config;
                context.arguments = arguments;
                context.filePath = config->GetPrecompiledSource();
                context.save = true;

                if (!ParseSourceFile(context))
                {
                    return false;
                }
            }

            for (auto& source : project->GetSources())
            {
                if (internal::IsHeaderFile(source))
                {
                    FileContext context;

                    context.config = config;
                    context.arguments = arguments;
                    context.filePath = source;
                    context.includePrecompiled = true;

                    if (!ParseSourceFile(context))
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    bool Parser::ParseSourceFile(FileContext& context)
    {
        std::cout << ">>> file    : " << context.filePath << std::endl;

        if (context.includePrecompiled && context.config->HasPrecompiledHeader())
        {
            auto pchFile = context.config->GetPrecompiledHeader();

            if (false)
            {
                pchFile = context.config->GetPrecompiledSource() + ".pch";
                if (!outputDirectory_.str().empty())
                {
                    pchFile = (outputDirectory_ / pchFile).str();
                }
            }

            context.arguments.Add("--include");
            context.arguments.Add(pchFile);
        }

        if (context.saveDependencies)
        {
            auto depFile = context.filePath.filename() + ".d";
            if (!outputDirectory_.str().empty())
            {
                depFile = (outputDirectory_ / depFile).str();
            }

            context.arguments.Add("-MMD");
            context.arguments.Add("-MF");
            context.arguments.Add(depFile);
        }

        clang::TranslationUnit translationUnit;

        unsigned options = CXTranslationUnit_SkipFunctionBodies;

        if (context.save)
        {
            options |= CXTranslationUnit_ForSerialization;
            options |= CXTranslationUnit_Incomplete;
        }

        auto result = pimpl_->GetIndex().ParseSourceFile(context.filePath.str(), context.arguments, options, translationUnit);

        internal::DisplayDiagnostics(translationUnit);

        if (translationUnit)
        {
            clang::NamespaceVisitor visitor(pimpl_->GetTypeRegistry());
            visitor.Visit(translationUnit.GetCursor());

            if (context.save)
            {
                auto saveFile = context.filePath.filename() + ".pch";
                auto savePath = !outputDirectory_.str().empty() ? outputDirectory_ / saveFile : saveFile;

                translationUnit.Save(savePath.str());
            }
        }
        else
        {
            auto errorString = [](auto errorCode)
            {
                switch (errorCode)
                {
                    case CXError_Success: return "success";
                    case CXError_Failure: return "failure";
                    case CXError_Crashed: return "crashed";
                    case CXError_InvalidArguments: return "invalid arguments";
                    case CXError_ASTReadError: return "ast read error";
                }
            };

            std::cout << std::endl;
            std::cout << "failed to create TranslationUnit (" << errorString(result) << ")" << std::endl;
            std::cout << std::endl;

            return false;
        }

        return true;
    }
}
