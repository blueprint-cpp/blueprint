#include "Blueprint/Parser/Clang/Index.hpp"

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

    TranslationUnit Index::ParseSourceFile(const std::string& file, int argc, const char** argv, unsigned options) const
    {
        return clang_parseTranslationUnit(
            index_,
            file.c_str(),
            argv,
            argc,
            nullptr, // unsavedFiles
            0,       // unsavedFilesCount
            options
        );
    }
}
}
