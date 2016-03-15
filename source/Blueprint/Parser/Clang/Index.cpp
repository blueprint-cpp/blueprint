#include "Blueprint/Parser/Clang/Index.hpp"

#if defined(EXTERN_CLANG_ENABLED)

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

    TranslationUnit Index::ParseSourceFile(const std::string& file, const CommandLineArguments& arguments, unsigned options) const
    {
        std::vector<const char*> args;

        args.reserve(arguments.GetArguments().size());

        for (auto& argument : arguments.GetArguments())
        {
            args.push_back(argument.c_str());
        }

        return clang_parseTranslationUnit(
            index_,
            file.c_str(),
            &args[0],
            (int)args.size(),
            nullptr, // unsavedFiles
            0,       // unsavedFilesCount
            options
        );
    }
}
}

#endif
