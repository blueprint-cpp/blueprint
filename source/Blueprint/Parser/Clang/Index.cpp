#include "Blueprint/Parser/Clang/Index.hpp"

#include "Blueprint/Parser/CommandLineArguments.hpp"

namespace blueprint
{
namespace clang
{
    Index::Index()
    {
        // excludeDeclarationsFromPCH = 1
        // displayDiagnostics = 1
        index_ = clang_createIndex(1, 1);
    }

    Index::~Index()
    {
        clang_disposeIndex(index_);
    }

    CXErrorCode Index::ParseSourceFile(const std::string& file, const CommandLineArguments& arguments, unsigned options, TranslationUnit& translationUnit) const
    {
        std::vector<const char*> args;

        args.reserve(arguments.GetArguments().size());

        for (auto& argument : arguments.GetArguments())
        {
            args.push_back(argument.c_str());
        }

        CXTranslationUnit tu;

        auto result = clang_parseTranslationUnit2(
            index_,
            file.c_str(),
            &args[0],
            (int)args.size(),
            nullptr, // unsavedFiles
            0,       // unsavedFilesCount
            options,
            &tu
        );

        translationUnit = TranslationUnit(tu);

        return result;
    }
}
}
