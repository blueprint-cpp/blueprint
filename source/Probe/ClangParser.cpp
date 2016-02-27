#include "Probe/ClangParser.hpp"

#if defined(EXTERN_CLANG_ENABLED)

#include "Probe/JsonImporter.hpp"
#include "Probe/Workspace.hpp"

namespace probe
{
    bool ClangParser::Parse(const std::string& filename)
    {
        auto workspace = JsonImporter::ImportWorkspace(filename);
        return Parse(workspace.get());
    }

    bool ClangParser::Parse(const Workspace* workspace)
    {
        if (workspace == nullptr)
        {
            return false;
        }

        std::cout << "> Workspace : " << workspace->GetName() << std::endl;

        for (auto& project : workspace->GetProjects())
        {
            std::cout << ">> Project : " << project->GetName() << std::endl;
        }

        return true;
    }
}

#endif
