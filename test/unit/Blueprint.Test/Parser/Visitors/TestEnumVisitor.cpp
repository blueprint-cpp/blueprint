#include <catch/catch.hpp>

#include "Blueprint/Parser/Visitors/EnumVisitor.hpp"
#include "BlueprintReflection/Registry/TypeRegistry.hpp"
#include "BlueprintReflection/Type/EnumType.hpp"
#include "TestHelpers/BufferParser.hpp"

using namespace blueprint;
using namespace blueprint::clang;
using namespace blueprint::reflection;

struct EnumVisitorFixture
{
    TypeRegistry typeRegistry_;
    Namespace namespace_;

    VisitContext visitContext_{typeRegistry_, namespace_};
};

TEST_CASE_METHOD(EnumVisitorFixture, "TestEnumVisitor")
{
    SECTION("Enum")
    {
        std::string fileBuffer = R"(
            enum SomeEnum
            {
                SM_Value_A,
                SM_Value_B
            };
        )";

        unittest::BufferParser parser;

        auto tu = parser.Parse(fileBuffer);
        auto cursor = parser.FindChildOfKind(tu.GetCursor(), CXCursor_EnumDecl);
        REQUIRE(cursor.IsNull() == false);

        EnumVisitor::Visit(visitContext_, cursor);

        CHECK(typeRegistry_.GetTypeCount() == 1);

        auto type = typeRegistry_.Find("SomeEnum");
        REQUIRE(type != nullptr);
        CHECK(type->GetName() == "SomeEnum");

        auto enumType = dynamic_cast<const EnumType*>(type);
        REQUIRE(enumType != nullptr);
        REQUIRE(enumType->GetEntries().size() == 2);
        CHECK(enumType->GetEntries()[0].first  == "SM_Value_A");
        CHECK(enumType->GetEntries()[0].second == 0);
        CHECK(enumType->GetEntries()[1].first  == "SM_Value_B");
        CHECK(enumType->GetEntries()[1].second == 1);
        CHECK(enumType->GetSize() == sizeof(int));
    }

    SECTION("Enum Class")
    {
        std::string fileBuffer = R"(
            enum class SomeEnumClass
            {
                Value_A = 8,
                Value_B = 3
            };
        )";

        unittest::BufferParser parser;

        auto tu = parser.Parse(fileBuffer);
        auto cursor = parser.FindChildOfKind(tu.GetCursor(), CXCursor_EnumDecl);
        REQUIRE(cursor.IsNull() == false);

        EnumVisitor::Visit(visitContext_, cursor);

        CHECK(typeRegistry_.GetTypeCount() == 1);

        auto type = typeRegistry_.Find("SomeEnumClass");
        REQUIRE(type != nullptr);
        CHECK(type->GetName() == "SomeEnumClass");

        auto enumType = dynamic_cast<const EnumType*>(type);
        REQUIRE(enumType != nullptr);
        REQUIRE(enumType->GetEntries().size() == 2);
        CHECK(enumType->GetEntries()[0].first  == "Value_A");
        CHECK(enumType->GetEntries()[0].second == 8);
        CHECK(enumType->GetEntries()[1].first  == "Value_B");
        CHECK(enumType->GetEntries()[1].second == 3);
        CHECK(enumType->GetSize() == sizeof(int));
    }
}
