#pragma once

#if defined(EXTERN_CLANG_ENABLED)

namespace probe
{
    class Workspace;

    class ClangParser
    {
    public:
        bool Parse(const std::string& filename);
        bool Parse(const Workspace* workspace);
    };
}

#endif
