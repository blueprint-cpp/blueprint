#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

#include "Blueprint/Parser/Clang/String.hpp"
#include "Blueprint/Utilities/WorkingDirectory.hpp"

void ChangeCWD(int argc, const char* argv[])
{
    if (argc < 2)
        return;

    std::string cwd;
    blueprint::WorkingDirectory::SetCurrent(argv[1]);
    cwd = blueprint::WorkingDirectory::GetCurrent();

    std::cout << "{ cwd : " << cwd << " }" << std::endl;
}

int main(int argc, const char* argv[])
{
    ChangeCWD(argc, argv);

    std::cout << "{ libclang index version " << CINDEX_VERSION_STRING << " }" << std::endl;
    std::cout << "{ libclang " << blueprint::clang::String(clang_getClangVersion()).Get() << " }" << std::endl;

    return Catch::Session().run();
}
