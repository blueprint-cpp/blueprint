#include "Probe/ClangParser.hpp"

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

#if defined(EXTERN_CLANG_ENABLED)
    probe::ClangParser parser;
    parser.Parse("invalid_file");
#endif

    return 0;
}
