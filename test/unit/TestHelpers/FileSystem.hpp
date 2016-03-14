#pragma once

#include <filesystem/path.h>

inline std::string NormalizedPath(const filesystem::path& path)
{
    return path.str(filesystem::path::posix_path);
}
