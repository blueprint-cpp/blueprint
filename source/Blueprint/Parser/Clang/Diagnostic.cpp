#include "Blueprint/Parser/Clang/Diagnostic.hpp"

#if defined(EXTERN_CLANG_ENABLED)

namespace blueprint
{
namespace clang
{
    Diagnostic::Diagnostic(CXDiagnostic diagnostic)
        : diagnostic_(diagnostic)
    {}

    Diagnostic::~Diagnostic()
    {
        if (diagnostic_)
        {
            clang_disposeDiagnostic(diagnostic_);
        }
    }

    Diagnostic::operator CXDiagnostic() const
    {
        return diagnostic_;
    }

    Diagnostic::operator bool() const
    {
        return diagnostic_ != nullptr;
    }

    unsigned Diagnostic::GetDefaultOptions()
    {
        return clang_defaultDiagnosticDisplayOptions();
    }

    String Diagnostic::Format(unsigned options) const
    {
        return clang_formatDiagnostic(diagnostic_, options);
    }
}
}

#endif
