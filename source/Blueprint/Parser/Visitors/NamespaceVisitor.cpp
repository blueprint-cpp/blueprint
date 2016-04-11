#include "Blueprint/Parser/Visitors/NamespaceVisitor.hpp"

#include "BlueprintClang/Cursor.hpp"
#include "Blueprint/Parser/Visitors/ClassVisitor.hpp"
#include "Blueprint/Parser/Visitors/EnumVisitor.hpp"
#include "BlueprintReflection/Registry/TypeRegistry.hpp"
#include "BlueprintReflection/Type/ClassType.hpp"
#include "BlueprintReflection/Type/EnumType.hpp"

namespace blueprint
{
namespace clang
{
    NamespaceVisitor::NamespaceVisitor(reflection::TypeRegistry& typeRegistry)
        : typeRegistry_(typeRegistry)
    {}

    NamespaceVisitor::NamespaceVisitor(reflection::TypeRegistry& typeRegistry, const reflection::Namespace& ns)
        : typeRegistry_(typeRegistry)
        , namespace_(ns)
    {}

    void NamespaceVisitor::Visit(const clang::Cursor& cursor)
    {
        assert(cursor.IsOfKind(CXCursor_Namespace) || cursor.IsOfKind(CXCursor_TranslationUnit));

        for (auto& child : cursor.GetChildren())
        {
            if (child.IsInSystemHeader())
            {
                continue;
            }

            switch (child.GetKind())
            {
                case CXCursor_Namespace:
                {
                    std::string spelling = child.GetSpelling().Get();

                    if (spelling.empty())
                    {
                        spelling = "{anonymous}";
                    }

                    NamespaceVisitor visitor(typeRegistry_, namespace_.Push(spelling));
                    visitor.Visit(child);
                }
                break;

                case CXCursor_ClassTemplate:
                {
                    // TODO
                }
                break;

                case CXCursor_ClassDecl:
                case CXCursor_StructDecl:
                {
                    VisitContext context(typeRegistry_, namespace_);
                    ClassVisitor::Visit(context, child);
                }
                break;

                case CXCursor_EnumDecl:
                {
                    VisitContext context(typeRegistry_, namespace_);
                    EnumVisitor::Visit(context, child);
                }
                break;

                default:
                    break;
            }
        }
    }
}
}
