#include "BlueprintApp/Application.hpp"

#include "Blueprint/Parser/Parser.hpp"

#include <clara/clara.h>
#include <iostream>

namespace blueprint
{
    namespace internal
    {
        struct Options
        {
            std::string processName;
            std::string filename;

            bool showHelp{false};
            bool listTypes{false};
            bool verbose{false};
        };

        Clara::CommandLine<Options> CreateCommandLine()
        {
            Clara::CommandLine<Options> commandLine;

            commandLine.setThrowOnUnrecognisedTokens(true);
            commandLine.bindProcessName(&Options::processName);

            commandLine["-h"]["--help"]
                .describe("display usage information")
                .bind(&Options::showHelp);

            commandLine["-l"]["--list-types"]
                .describe("list all types parsed")
                .bind(&Options::listTypes);

            commandLine["-v"]["--verbose"]
                .describe("parse with clang in verbose mode")
                .bind(&Options::verbose);

            commandLine["-f"]["--file"]
                .describe("filename of the workspace to parse")
                .bind(&Options::filename, "filename");

            return commandLine;
        }

        void PrintInputError(const std::string& message)
        {
            std::cerr
                << std::endl << "Error(s) in input:" << std::endl
                << Tbc::Text(message, Tbc::TextAttributes().setIndent(2))
                << std::endl << std::endl;
        }
    }

    struct Application::Impl
    {
        Clara::CommandLine<internal::Options> commandLine{internal::CreateCommandLine()};
        internal::Options options;
    };

    Application::Application()
        : pimpl_(std::make_unique<Impl>())
    {}

    Application::~Application() = default;

    int Application::Run(int argc, const char* argv[])
    {
        try
        {
            pimpl_->commandLine.parseInto(argc, argv, pimpl_->options);
        }
        catch (std::exception& e)
        {
            internal::PrintInputError(e.what());
            ShowHelp();
            return 1;
        }

        return Run();
    }

    int Application::Run()
    {
        auto& options = pimpl_->options;

        if (options.showHelp)
        {
            ShowHelp();
            return 0;
        }

        if (options.filename.empty())
        {
            internal::PrintInputError("no input file");
            ShowHelp();
            return 0;
        }

        blueprint::Parser parser;
        parser.SetListTypes(options.listTypes);
        parser.SetVerbose(options.verbose);
        parser.ParseWorkspace(options.filename);

        return 0;
    }

    void Application::ShowHelp()
    {
        pimpl_->commandLine.usage(std::cout, pimpl_->options.processName);
    }
}
