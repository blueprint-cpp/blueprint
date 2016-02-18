#pragma once

#include <Probe/Project.hpp>
#include <Probe/Solution.hpp>

#include <memory>
#include <string>

namespace probe
{
    class JsonImporter
    {
    public:
        static std::unique_ptr<Solution> ImportSolution(const std::string& filename);
        static std::unique_ptr<Project>  ImportProject( const std::string& filename);
    };
}
