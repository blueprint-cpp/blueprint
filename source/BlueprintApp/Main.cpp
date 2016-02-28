#include "Blueprint/Parser/ClangParser.hpp"

int main(int argc, char* argv[])
{
    const char* filename = nullptr;

    if (argc > 1)
    {
        filename = argv[1];
    }

#if defined(EXTERN_CLANG_ENABLED)
    blueprint::ClangParser parser;
    parser.ParseWorkspace(filename);
#endif

    return 0;
}
