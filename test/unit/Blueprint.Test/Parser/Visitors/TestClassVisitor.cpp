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

        size_t expectedPadding = 3;
        CHECK(classType->GetSize() == sizeof(int) + sizeof(float) + sizeof(bool) + expectedPadding);
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

        size_t expectedPadding = 3;
        CHECK(classType->GetSize() == sizeof(int) + sizeof(float) + sizeof(bool) + expectedPadding);

    }

    SECTION("Inheritance")
    {
        SECTION("Single")
        {
            std::string fileBuffer = R"(
                class Base {};
                class Derived : public Base {};
            )";

            unittest::BufferParser parser;

            auto tu = parser.Parse(fileBuffer);

            for (auto& child : tu.GetCursor().GetChildren())
            {
                if (child.IsOfKind(CXCursor_ClassDecl))
                {
                    ClassVisitor visitor;
                    visitor.Visit(visitContext_, child);
                }
            }

            CHECK(typeRegistry_.GetTypeCount() == 2);

            auto base = dynamic_cast<const ClassType*>(typeRegistry_.Find("Base"));
            auto derived = dynamic_cast<const ClassType*>(typeRegistry_.Find("Derived"));

            CHECK(base != nullptr);
            REQUIRE(derived != nullptr);

            REQUIRE(derived->GetBaseClasses().size() == 1);
            REQUIRE(derived->GetBaseClasses()[0] == base);
        }

        SECTION("Multiple")
        {
            std::string fileBuffer = R"(
                class BaseA {};
                class BaseB {};
                class BaseC {};
                class Derived : public BaseA, public BaseB, public BaseC {};
            )";

            unittest::BufferParser parser;

            auto tu = parser.Parse(fileBuffer);

            for (auto& child : tu.GetCursor().GetChildren())
            {
                if (child.IsOfKind(CXCursor_ClassDecl))
                {
                    ClassVisitor visitor;
                    visitor.Visit(visitContext_, child);
                }
            }

            CHECK(typeRegistry_.GetTypeCount() == 4);

            auto baseA = dynamic_cast<const ClassType*>(typeRegistry_.Find("BaseA"));
            auto baseB = dynamic_cast<const ClassType*>(typeRegistry_.Find("BaseB"));
            auto baseC = dynamic_cast<const ClassType*>(typeRegistry_.Find("BaseC"));
            auto derived = dynamic_cast<const ClassType*>(typeRegistry_.Find("Derived"));

            CHECK(baseA != nullptr);
            CHECK(baseB != nullptr);
            CHECK(baseC != nullptr);
            REQUIRE(derived != nullptr);

            REQUIRE(derived->GetBaseClasses().size() == 3);
            REQUIRE(derived->GetBaseClasses()[0] == baseA);
            REQUIRE(derived->GetBaseClasses()[1] == baseB);
            REQUIRE(derived->GetBaseClasses()[2] == baseC);
        }
    }
}

#endif
