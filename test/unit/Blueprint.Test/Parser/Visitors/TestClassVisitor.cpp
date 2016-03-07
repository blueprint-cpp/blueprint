#include <catch/catch.hpp>

#if defined(EXTERN_CLANG_ENABLED)

#include "TestHelpers/BufferParser.hpp"
#include "Blueprint/Parser/Visitors/ClassVisitor.hpp"
#include "Blueprint/Reflection/ClassType.hpp"
#include "Blueprint/Reflection/TypeRegistry.hpp"

using namespace blueprint;
using namespace blueprint::reflection;

struct ClassVisitorFixture
{
    TypeRegistry typeRegistry_;
    Namespace namespace_;

    VisitContext visitContext_{typeRegistry_, namespace_};
};

TEST_CASE_METHOD(ClassVisitorFixture, "TestClassVisitor")
{
    SECTION("Struct")
    {
        std::string fileBuffer = R"(
            struct SomeStruct
            {};
        )";

        unittest::BufferParser parser;

        auto tu     = parser.Parse(fileBuffer);
        auto cursor = parser.FindChildOfKind(tu.GetCursor(), CXCursor_StructDecl);

        REQUIRE(cursor.IsNull() == false);

        ClassVisitor visitor;
        visitor.Visit(visitContext_, cursor);

        CHECK(typeRegistry_.GetTypeCount() == 1);

        auto type = typeRegistry_.Find("SomeStruct");
        REQUIRE(type != nullptr);
        CHECK(type->GetName() == "SomeStruct");

        auto classType = dynamic_cast<const ClassType*>(type);
        REQUIRE(classType != nullptr);
    }

    SECTION("Class")
    {
        std::string fileBuffer = R"(
            class SomeClass
            {};
        )";

        unittest::BufferParser parser;

        auto tu     = parser.Parse(fileBuffer);
        auto cursor = parser.FindChildOfKind(tu.GetCursor(), CXCursor_ClassDecl);

        REQUIRE(cursor.IsNull() == false);

        ClassVisitor visitor;
        visitor.Visit(visitContext_, cursor);

        CHECK(typeRegistry_.GetTypeCount() == 1);

        auto type = typeRegistry_.Find("SomeClass");
        REQUIRE(type != nullptr);
        CHECK(type->GetName() == "SomeClass");

        auto classType = dynamic_cast<const ClassType*>(type);
        REQUIRE(classType != nullptr);
    }
}

#endif
