#include "Blueprint/Utilities/WorkingDirectory.hpp"

#if defined(_MSC_VER)
    #include <windows.h>
#else
    #include <unistd.h>
#endif

namespace blueprint
{
    void WorkingDirectory::SetCurrent(const std::string& directory)
    {
    #if defined(_MSC_VER)
        #if defined(UNICODE)
            std::wstring tmp(directory.begin(), directory.end());
            SetCurrentDirectory(tmp.c_str());
        #else
            SetCurrentDirectory(directory.c_str());
        #endif
    #else
        chdir(directory.c_str());
    #endif
    }

    std::string WorkingDirectory::GetCurrent()
    {
    #if defined(_MSC_VER)
        #if defined(UNICODE)
            wchar_t tmp[256];
            GetCurrentDirectory(sizeof(tmp), tmp);
            std::wstring tmp2(tmp);
            std::string cwd(tmp2.begin(), tmp2.end());
        #else
            char cwd[256];
            GetCurrentDirectory(sizeof(cwd), cwd);
        #endif
    #else
        char cwd[256];
        getcwd(cwd, sizeof(cwd));
    #endif

        return cwd;
    }
}
