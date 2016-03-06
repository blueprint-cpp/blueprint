#include "Blueprint/Parser/Visitors/NamespaceVisitor.hpp"

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/Cursor.hpp"
#include "Blueprint/Parser/Visitors/ClassVisitor.hpp"
#include "Blueprint/Parser/Visitors/EnumVisitor.hpp"
#include "Blueprint/Reflection/ClassType.hpp"
#include "Blueprint/Reflection/EnumType.hpp"
#include "Blueprint/Reflection/TypeRegistry.hpp"

#include <cassert>

namespace blueprint
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

#endif
