#pragma once

#if defined(_MSC_VER)
    #pragma warning(push)
    #pragma warning(disable : 4267)
#elif defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

#include <sqlite3pp/sqlite3pp.h>

#if defined(_MSC_VER)
    #pragma warning(pop)
#elif defined(__clang__)
    #pragma clang diagnostic pop
#endif
