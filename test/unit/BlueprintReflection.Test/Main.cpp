#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

int main(int argc, const char* argv[])
{
    return Catch::Session().run(argc, argv);
}
