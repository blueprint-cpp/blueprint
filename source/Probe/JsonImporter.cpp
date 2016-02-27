#include "Probe/JsonImporter.hpp"

#include "Probe/Configuration.hpp"

#include "filesystem/path.h"
#include "filesystem/resolver.h"
#include "json/json.hpp"

#include <fstream>
#include <sstream>

namespace probe
{
    namespace internal
    {
        nlohmann::json ParseJsonFile(const filesystem::path& filePath)
        {
            std::ifstream file(filePath.str());

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

            if (config["pchsource"].is_string())
            {
                configuration->SetPrecompiledHeader(config["pchsource"]);
            }

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

    std::unique_ptr<Workspace> JsonImporter::ImportWorkspace(const filesystem::path& path)
    {
        auto json = internal::ParseJsonFile(path);

        if (json.is_object())
        {
            auto directory = path.parent_path();
            auto workspace = std::make_unique<Workspace>();

            workspace->SetName(json["workspace"]);
            workspace->SetDirectory(directory.str());

            auto& projects = json["projects"];

            if (projects.is_array())
            {
                for (auto& project : projects)
                {
                    auto projectPath = directory / project;
                    workspace->AddProject(ImportProject(projectPath.str()));
                }
            }

            return workspace;
        }

        return nullptr;
    }

    std::unique_ptr<Project> JsonImporter::ImportProject(const filesystem::path& path)
    {
        auto json = internal::ParseJsonFile(path);

        if (json.is_object())
        {
            auto directory = path.parent_path();
            auto project = std::make_unique<Project>();

            project->SetName(json["project"]);
            project->SetDirectory(directory.str());

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
