#include "BlueprintClang/Index.hpp"

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

    CXErrorCode Index::ParseSourceFile(const std::string& file, const std::vector<std::string>& arguments, unsigned options, TranslationUnit& translationUnit) const
    {
        std::vector<const char*> args;

        args.reserve(arguments.size());

        for (auto& argument : arguments)
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
