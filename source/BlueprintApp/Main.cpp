#include "Blueprint/Parser/Parser.hpp"

#include <clara/clara.h>
#include <iostream>

struct Options
{
    bool showHelp{false};

    std::string processName;
    std::string filename;
};

class Application
{
public:
    int Run(int argc, const char* argv[])
    {
        InitCommandLine();

        try
        {
            m_CommandLine.parseInto(argc, argv, m_Options);
        }
        catch (std::exception& e)
        {
            PrintInputError(e.what());
            ShowHelp();
            return 1;
        }

        return Run();
    }

private:
    int Run()
    {
        if (m_Options.showHelp)
        {
            ShowHelp();
            return 0;
        }

        if (m_Options.filename.empty())
        {
            PrintInputError("no input file");
            ShowHelp();
            return 0;
        }

    #if defined(EXTERN_CLANG_ENABLED)
        blueprint::Parser().ParseWorkspace(m_Options.filename);
    #else
        std::cout << "clang is not available" << std::endl;
    #endif

        return 0;
    }

    void InitCommandLine()
    {
        m_CommandLine.setThrowOnUnrecognisedTokens(true);
        m_CommandLine.bindProcessName(&Options::processName);

        m_CommandLine["-h"]["--help"]
            .describe("display usage information")
            .bind(&Options::showHelp);

        m_CommandLine["-f"]["--file"]
            .describe("filename of the workspace to parse")
            .bind(&Options::filename, "filename");
    }

    void PrintInputError(const std::string& message)
    {
        std::cerr
            << std::endl << "Error(s) in input:" << std::endl
            << Tbc::Text(message, Tbc::TextAttributes().setIndent(2))
            << std::endl << std::endl;
    }

    void ShowHelp()
    {
        m_CommandLine.usage(std::cout, m_Options.processName);
    }

private:
    Clara::CommandLine<Options> m_CommandLine;
    Options m_Options;
};

int main(int argc, const char* argv[])
{

    return Application().Run(argc, argv);
}
