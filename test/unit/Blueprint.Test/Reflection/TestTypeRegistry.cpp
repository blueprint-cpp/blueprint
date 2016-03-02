#include <catch/catch.hpp>

#include "Blueprint/Reflection/TypeInfo.hpp"
#include "Blueprint/Reflection/TypeRegistry.hpp"

TEST_CASE("TestTypeRegistry")
{
    using namespace blueprint::reflection;

    TypeRegistry registry;

    SECTION("Default State")
    {
        CHECK(registry.GetTypeCount() == 0);
    }

    SECTION("Register")
    {
        auto typeA = std::make_unique<TypeInfo>();
        typeA->SetTypeId(0xA);

        registry.Register(std::move(typeA));

        CHECK(registry.GetTypeCount() == 1);
        CHECK(registry.Contains(0xA));

        auto typeB = std::make_unique<TypeInfo>();
        typeB->SetTypeId(0xB);

        registry.Register(std::move(typeB));

        CHECK(registry.GetTypeCount() == 2);
        CHECK(registry.Contains(0xB));
    }

    SECTION("Find")
    {
        SECTION("Returns null if not found")
        {
            uint64_t invalidId = 0xdeadbeef;

            CHECK(registry.Contains(invalidId) == false);
            CHECK(registry.Find(invalidId) == nullptr);
        }

        SECTION("Returns the registered type")
        {
            auto typeA = std::make_unique<TypeInfo>();
            typeA->SetTypeId(0xA);
            typeA->SetName("type_A");

            registry.Register(std::move(typeA));

            auto foundA = registry.Find(0xA);
            REQUIRE(foundA != nullptr);
            CHECK(foundA->GetTypeId() == 0xA);
            CHECK(foundA->GetName() == "type_A");
            CHECK(foundA->GetNamespace().IsGlobal());

            auto typeB = std::make_unique<TypeInfo>();
            typeB->SetTypeId(0xB);
            typeB->SetName("type_B");
            typeB->SetNamespace("some::scope");

            registry.Register(std::move(typeB));

            auto foundB = registry.Find(0xB);
            REQUIRE(foundB != nullptr);
            CHECK(foundB->GetTypeId() == 0xB);
            CHECK(foundB->GetName() == "type_B");
            CHECK(foundB->GetNamespace().ToString() == "some::scope");
        }
    }
}
