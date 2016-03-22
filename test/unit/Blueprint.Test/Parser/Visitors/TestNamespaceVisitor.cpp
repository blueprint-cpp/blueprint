#include <catch/catch.hpp>

#include "Blueprint/Parser/Visitors/NamespaceVisitor.hpp"
#include "Blueprint/Reflection/TypeRegistry.hpp"
#include "TestHelpers/BufferParser.hpp"

using namespace blueprint;
using namespace blueprint::clang;
using namespace blueprint::reflection;

struct NamespaceVisitorFixture
{
    TypeRegistry typeRegistry_;
};

TEST_CASE_METHOD(NamespaceVisitorFixture, "TestNamespaceVisitor")
{
    SECTION("Global Namespace")
    {
        std::string fileBuffer = R"(
            struct SomeStruct {};
            class SomeClass {};
            enum SomeEnum {};
        )";

        unittest::BufferParser parser;

        auto tu = parser.Parse(fileBuffer);
        auto cursor = tu.GetCursor();
        REQUIRE(cursor.IsNull() == false);

        NamespaceVisitor visitor(typeRegistry_);
        visitor.Visit(tu.GetCursor());

        CHECK(typeRegistry_.GetTypeCount() == 3);

        CHECK(typeRegistry_.Find("SomeStruct") != nullptr);
        CHECK(typeRegistry_.Find("SomeClass") != nullptr);
        CHECK(typeRegistry_.Find("SomeEnum") != nullptr);
    }

    SECTION("Namespace")
    {
        std::string fileBuffer = R"(
            namespace scopeA
            {
                struct SomeStruct {};
                class SomeClass {};

                namespace scopeB
                {
                    enum SomeEnum {};
                }
            }
        )";

        unittest::BufferParser parser;

        auto tu = parser.Parse(fileBuffer);
        auto cursor = tu.GetCursor();
        REQUIRE(cursor.IsNull() == false);

        NamespaceVisitor visitor(typeRegistry_);
        visitor.Visit(tu.GetCursor());

        CHECK(typeRegistry_.GetTypeCount() == 3);

        CHECK(typeRegistry_.Find("scopeA::SomeStruct") != nullptr);
        CHECK(typeRegistry_.Find("scopeA::SomeClass") != nullptr);
        CHECK(typeRegistry_.Find("scopeA::scopeB::SomeEnum") != nullptr);
    }
}
