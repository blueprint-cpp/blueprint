#include "Blueprint/Parser/Parser.hpp"

int main(int argc, char* argv[])
{
    const char* filename = nullptr;

    if (argc > 1)
    {
        filename = argv[1];
    }

#if defined(EXTERN_CLANG_ENABLED)
    blueprint::Parser parser;
    parser.ParseWorkspace(filename);
#endif

    return 0;
}
