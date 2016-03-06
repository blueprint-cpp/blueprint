#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

#include "Blueprint/Utilities/WorkingDirectory.hpp"

#if defined(EXTERN_CLANG_ENABLED)
#include <clang-c/Index.h>
#endif

void ChangeCWD( int argc, char* argv[] )
{
    if ( argc < 2 )
        return;

    std::string cwd;
    blueprint::WorkingDirectory::SetCurrent(argv[1]);
    cwd = blueprint::WorkingDirectory::GetCurrent();

    std::cout << "{ cwd : " << cwd << " }" << std::endl;
}

int main( int argc, char* argv[] )
{
    ChangeCWD( argc, argv );

#if defined(EXTERN_CLANG_ENABLED)
    std::cout << "{ libclang : " << CINDEX_VERSION_STRING << " }" << std::endl;
#endif

    return Catch::Session().run();
}
