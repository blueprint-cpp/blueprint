#include "Blueprint/Workspace/JsonImporter.hpp"

#include <json/json.hpp>

#include <fstream>
#include <sstream>

namespace blueprint
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

    std::unique_ptr<Workspace> JsonImporter::ImportWorkspace(const filesystem::path& workspaceFile)
    {
        auto json = internal::ParseJsonFile(workspaceFile);

        if (json.is_object())
        {
            auto workspace = std::make_unique<Workspace>();

            workspace->SetName(json["workspace"]);
            workspace->SetFile(workspaceFile);

            auto& projects = json["projects"];

            if (projects.is_array())
            {
                auto workspacePath = workspaceFile.parent_path();

                for (auto& project : projects)
                {
                    auto projectPath = workspacePath / project;
                    workspace->AddProject(ImportProject(projectPath));
                }
            }

            return workspace;
        }

        return nullptr;
    }

    std::unique_ptr<Project> JsonImporter::ImportProject(const filesystem::path& projectFile)
    {
        auto json = internal::ParseJsonFile(projectFile);

        if (json.is_object())
        {
            auto project = std::make_unique<Project>();

            project->SetName(json["project"]);
            project->SetFile(projectFile);

            for (auto& config : json["configs"])
            {
                project->AddConfiguration(internal::ImportConfig(config));
            }

            for (auto& source : json["files"])
            {
                project->AddSource(source);
            }

            return project;
        }

        return nullptr;
    }
}
