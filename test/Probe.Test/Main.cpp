#define CATCH_CONFIG_RUNNER
#include "catch/catch.hpp"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

void ChangeCWD( int argc, char* argv[] )
{
    if ( argc < 2 )
        return;

    char cwd[256];

#ifdef _MSC_VER
    SetCurrentDirectory(argv[1]);
    GetCurrentDirectory(sizeof(cwd), cwd);
#else
    chdir(argv[1]);
    getcwd(cwd, sizeof(cwd));
#endif

    std::cout << "{ cwd : " << cwd << " }" << std::endl;
}

int main( int argc, char* argv[] )
{
    ChangeCWD( argc, argv );

    return Catch::Session().run();
}
