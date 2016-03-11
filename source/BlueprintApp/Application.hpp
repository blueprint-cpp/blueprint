#pragma once

#include <memory>

namespace blueprint
{
    class Application
    {
    public:
        Application();
        ~Application();

        int Run(int argc, const char* argv[]);

    private:
        int Run();

        void ShowHelp();

    private:
        struct Impl;
        std::unique_ptr<Impl> pimpl_;
    };
}
