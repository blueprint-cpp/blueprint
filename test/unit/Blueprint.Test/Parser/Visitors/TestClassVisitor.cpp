#include <catch/catch.hpp>

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Visitors/ClassVisitor.hpp"
#include "Blueprint/Reflection/ClassType.hpp"
#include "Blueprint/Reflection/TypeRegistry.hpp"
#include "TestHelpers/BufferParser.hpp"

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
            {
                int   valueA;
                float valueB;
                bool  valueC;
            };
        )";

        unittest::BufferParser parser;

        auto tu = parser.Parse(fileBuffer);

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

        REQUIRE(classType->GetFields().size() == 3);
        CHECK(classType->GetFields()[0] == Field("valueA", sizeof(int),   0));
        CHECK(classType->GetFields()[1] == Field("valueB", sizeof(float), sizeof(int)));
        CHECK(classType->GetFields()[2] == Field("valueC", sizeof(bool),  sizeof(int) + sizeof(float)));
    }

    SECTION("Class")
    {
        std::string fileBuffer = R"(
            class SomeClass
            {
                int   valueA;
                float valueB;
                bool  valueC;
            };
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

        REQUIRE(classType->GetFields().size() == 3);
        CHECK(classType->GetFields()[0] == Field("valueA", sizeof(int),   0));
        CHECK(classType->GetFields()[1] == Field("valueB", sizeof(float), sizeof(int)));
        CHECK(classType->GetFields()[2] == Field("valueC", sizeof(bool),  sizeof(int) + sizeof(float)));
    }
}

#endif
