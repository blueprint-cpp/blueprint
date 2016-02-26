#include "Probe/JsonImporter.hpp"

#include "Probe/Configuration.hpp"

#include "json/json.hpp"

#include <fstream>
#include <sstream>

namespace probe
{
    namespace internal
    {
        nlohmann::json ParseJsonFile(const std::string& filename)
        {
            std::ifstream file(filename);

            if (file.is_open())
            {
                std::stringstream stream;
                stream << file.rdbuf();

                return nlohmann::json::parse(stream.str());
            }

            return nullptr;
        }

        std::unique_ptr<Configuration> ImportConfig(const nlohmann::json& config)
        {
            auto configuration = std::make_unique<Configuration>();

            configuration->SetName(config["name"]);
            configuration->SetPrecompiledHeader(config["pchsource"]);

            for (auto& define : config["defines"])
            {
                configuration->AddDefine(define);
            }

            for (auto& include : config["includedirs"])
            {
                configuration->AddInclude(include);
            }

            return configuration;
        }
    }

    std::unique_ptr<Solution> JsonImporter::ImportSolution(const std::string& filename)
    {
        auto json = internal::ParseJsonFile(filename);

        if (json.is_object())
        {
            auto solution = std::make_unique<Solution>();

            solution->SetName(json["solution"]);

            auto& projects = json["projects"];

            if (projects.is_array())
            {
                for (auto& project : projects)
                {
                    solution->AddProject(ImportProject(project));
                }
            }

            return solution;
        }

        return nullptr;
    }

    std::unique_ptr<Project> JsonImporter::ImportProject(const std::string& filename)
    {
        auto json = internal::ParseJsonFile(filename);

        if (json.is_object())
        {
            auto project = std::make_unique<Project>();

            project->SetName(json["project"]);

            for (auto& config : json["configs"])
            {
                project->AddConfiguration(internal::ImportConfig(config));
            }

            for (auto& file : json["files"])
            {
                project->AddFile(file);
            }

            return project;
        }

        return nullptr;
    }
}
