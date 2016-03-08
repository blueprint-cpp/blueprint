#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/String.hpp"

namespace blueprint
{
namespace clang
{
    class Diagnostic
    {
    public:
        Diagnostic() = default;
        Diagnostic(CXDiagnostic diagnostic);
        Diagnostic(Diagnostic&& other);
        ~Diagnostic();

        Diagnostic& operator=(Diagnostic&& other);

        operator CXDiagnostic() const;
        operator bool() const;

    public:
        static unsigned GetDefaultOptions();

        String Format(unsigned options) const;

    private:
        CXDiagnostic diagnostic_{nullptr};
    };
}
}

#endif
