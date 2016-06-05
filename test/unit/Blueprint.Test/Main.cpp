#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

#include "BlueprintClang/String.hpp"
#include "Blueprint/Utilities/WorkingDirectory.hpp"

int main(int argc, const char* argv[])
{
    std::cout << "{ libclang index version " << CINDEX_VERSION_STRING << " }" << std::endl;
    std::cout << "{ libclang " << blueprint::clang::String(clang_getClangVersion()).Get() << " }" << std::endl;

    if (argc > 1)
    {
        return Catch::Session().run(argc - 1, &argv[1]);
    }
    else
    {
        return Catch::Session().run();
    }
}
