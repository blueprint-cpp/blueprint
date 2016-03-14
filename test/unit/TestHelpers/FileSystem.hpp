#pragma once

#include <filesystem/path.h>

inline bool operator==(const filesystem::path& lhs, const std::string& rhs)
{
    return lhs.str(filesystem::path::posix_path) == rhs;
}
