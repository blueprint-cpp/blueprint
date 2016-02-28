#include "Probe/ClangParser.hpp"

#if defined(EXTERN_CLANG_ENABLED)

#include "Probe/JsonImporter.hpp"
#include "Probe/Workspace.hpp"

#include <clang-c/Index.h>
#include <fstream>
#include <iostream>

namespace probe
{
    namespace internal
    {
        class ClangIndex
        {
        public:
            ClangIndex()
            {
                // excludeDeclarationsFromPCH = 1
                // displayDiagnostics = 1
                index_ = clang_createIndex(1, 1);
            }

            ~ClangIndex()
            {
                clang_disposeIndex(index_);
                index_ = nullptr;
            }

            operator CXIndex()
            {
                return index_;
            }

        private:
            CXIndex index_{nullptr};
        };

        class ClangArguments
        {
        public:
            ClangArguments(const std::vector<std::string>& arguments)
            {
                if (arguments.size() > 0)
                {
                    arguments_ = new const char*[arguments.size()];
                    count_ = arguments.size();

                    for (size_t i = 0; i < arguments.size(); ++i)
                    {
                        arguments_[i] = arguments[i].c_str();
                    }
                }
            }

            ~ClangArguments()
            {
                if (arguments_)
                {
                    delete [] arguments_;
                }
            }

            const char** GetArguments() const
            {
                return arguments_;
            }

            size_t GetCount() const
            {
                return count_;
            }

        private:
            const char** arguments_{nullptr};
            size_t count_{0};
        };

        class CommandLineArguments
        {
        public:
            void Add(const std::string& argument)
            {
                arguments_.push_back(argument);
            }

            void ImportConfig(const Configuration* config, const filesystem::path& path)
            {
                if (config)
                {
                    for (auto& define : config->GetDefines())
                    {
                        Add("-D" + define);
                    }

                    for (auto& include : config->GetIncludes())
                    {
                        Add("-I" + (path / include).str());
                    }
                }
            }

            const std::vector<std::string>& GetArguments()
            {
                return arguments_;
            }

        private:
            std::vector<std::string> arguments_;
        };
    }

    class ClangParser::Impl
    {
    public:
        CXIndex GetIndex()
        {
            return index_;
        }

    private:
        internal::ClangIndex index_;
    };

    ClangParser::ClangParser()
    : pimpl_(new Impl())
    {}

    ClangParser::~ClangParser() = default;

    bool ClangParser::ParseWorkspace(const filesystem::path& filePath)
    {
        auto workspace = JsonImporter::ImportWorkspace(filePath);
        return ParseWorkspace(workspace.get());
    }

    bool ClangParser::ParseWorkspace(const Workspace* workspace)
    {
        if (workspace == nullptr)
        {
            std::cout << "invalid workspace" << std::endl;
            return false;
        }

        std::cout << "> workspace : " << workspace->GetName() << std::endl;

        for (auto& project : workspace->GetProjects())
        {
            ParseProject(project.get());
        }

        return true;
    }

    bool ClangParser::ParseProject(const filesystem::path& filePath)
    {
        auto project = JsonImporter::ImportProject(filePath);
        return ParseProject(project.get());
    }

    bool ClangParser::ParseProject(const Project* project)
    {
        if (project == nullptr)
        {
            std::cout << "invalid project" << std::endl;
            return false;
        }

        std::cout << ">> project  : " << project->GetName() << std::endl;

        const Configuration* config = nullptr;

        if (project->GetConfigurations().size() > 0)
        {
            config = project->GetConfigurations()[0].get();
        }

        for (auto& source : project->GetSources())
        {
            ParseSourceFile(project->GetFile().parent_path() / source, config);
        }

        return true;
    }

    bool ClangParser::ParseSourceFile(const filesystem::path& filePath, const Configuration* config)
    {
        auto cwd = filesystem::path::getcwd().str();
        auto absolutePath = filePath.make_absolute().str();
        auto relativePath = "./" + absolutePath.substr(cwd.length() + 1, absolutePath.length() - cwd.length() - 1);

        std::cout << ">>> source  : " << relativePath << std::endl;

        CXUnsavedFile unsavedFiles;
        unsigned unsavedFileCount = 0;
        unsigned options = CXTranslationUnit_SkipFunctionBodies;

        internal::CommandLineArguments arguments;

        arguments.Add("-std=c++14");
        arguments.ImportConfig(config, filePath.parent_path());

        internal::ClangArguments clangArgs(arguments.GetArguments());

        auto translationUnit = clang_parseTranslationUnit(
            pimpl_->GetIndex(),
            relativePath.c_str(),
            clangArgs.GetArguments(),
            clangArgs.GetCount(),
            &unsavedFiles,
            unsavedFileCount,
            options);

        if (translationUnit)
        {
            clang_disposeTranslationUnit(translationUnit);
            translationUnit = nullptr;

            return true;
        }

        return false;
    }
}

#endif
