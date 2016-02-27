#include "Probe/JsonImporter.hpp"

#include "Probe/Configuration.hpp"

#include "json/json.hpp"

#include <fstream>
#include <sstream>

namespace probe
{
    namespace internal
    {
        std::string GetDirectory(const std::string& filePath)
        {
            auto pos = filePath.find_last_of('/');
            return pos > 0 ? filePath.substr(0, pos) : nullptr;
        }

        std::string Combine(const std::string& path1, const std::string path2)
        {
            return path1 + '/' + path2;
        }

        nlohmann::json ParseJsonFile(const std::string& filePath)
        {
            std::ifstream file(filePath);

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

    std::unique_ptr<Workspace> JsonImporter::ImportWorkspace(const std::string& filePath)
    {
        auto json = internal::ParseJsonFile(filePath);

        if (json.is_object())
        {
            auto directory = internal::GetDirectory(filePath);
            auto workspace = std::make_unique<Workspace>();

            workspace->SetName(json["workspace"]);
            workspace->SetDirectory(directory);

            auto& projects = json["projects"];

            if (projects.is_array())
            {
                for (auto& project : projects)
                {
                    auto projectPath = internal::Combine(directory, project);
                    workspace->AddProject(ImportProject(projectPath));
                }
            }

            return workspace;
        }

        return nullptr;
    }

    std::unique_ptr<Project> JsonImporter::ImportProject(const std::string& filePath)
    {
        auto json = internal::ParseJsonFile(filePath);

        if (json.is_object())
        {
            auto directory = internal::GetDirectory(filePath);
            auto project = std::make_unique<Project>();

            project->SetName(json["project"]);
            project->SetDirectory(directory);

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
