#include <catch/catch.hpp>

#include "Blueprint/Reflection/Type.hpp"
#include "Blueprint/Reflection/TypeRegistry.hpp"

using namespace blueprint::reflection;

struct TypeRegistryFixture
{
    std::unique_ptr<Type> CreateTypeA()
    {
        auto type = std::make_unique<Type>();

        type->SetTypeId(0xA);
        type->SetName("type_A");

        return std::move(type);
    }

    std::unique_ptr<Type> CreateTypeB()
    {
        auto type = std::make_unique<Type>();

        type->SetTypeId(0xB);
        type->SetName("type_B");
        type->SetNamespace("some::scope");

        return std::move(type);
    }

    void RegisterTypeA()
    {
        registry_.Register(CreateTypeA());
    }

    void RegisterTypeB()
    {
        registry_.Register(CreateTypeB());
    }

    TypeRegistry registry_;
};

TEST_CASE_METHOD(TypeRegistryFixture, "TestTypeRegistry")
{
    SECTION("Default State")
    {
        CHECK(registry_.GetTypeCount() == 0);
        CHECK(registry_.Contains(0xA) == false);
        CHECK(registry_.Contains(0xB) == false);
    }

    SECTION("Register")
    {
        registry_.Register(CreateTypeA());

        CHECK(registry_.GetTypeCount() == 1);
        CHECK(registry_.Contains(0xA));

        registry_.Register(CreateTypeB());

        CHECK(registry_.GetTypeCount() == 2);
        CHECK(registry_.Contains(0xB));
    }

    SECTION("Find")
    {
        SECTION("By Name")
        {
            uint64_t invalidId = 0xdeadbeef;
            CHECK(registry_.Find(invalidId) == nullptr);

            RegisterTypeA();

            auto foundA = registry_.Find("type_A");
            REQUIRE(foundA != nullptr);
            CHECK(foundA->GetTypeId() == 0xA);
            CHECK(foundA->GetName() == "type_A");
            CHECK(foundA->GetNamespace().IsGlobal());

            RegisterTypeB();

            auto foundB = registry_.Find(0xB);
            REQUIRE(foundB != nullptr);
            CHECK(foundB->GetTypeId() == 0xB);
            CHECK(foundB->GetName() == "type_B");
            CHECK(foundB->GetNamespace().ToString() == "some::scope");
        }

        SECTION("By Id")
        {
            uint64_t invalidId = 0xdeadbeef;
            CHECK(registry_.Find(invalidId) == nullptr);

            RegisterTypeA();

            auto foundA = registry_.Find(0xA);
            REQUIRE(foundA != nullptr);
            CHECK(foundA->GetTypeId() == 0xA);
            CHECK(foundA->GetName() == "type_A");
            CHECK(foundA->GetNamespace().IsGlobal());

            RegisterTypeB();

            auto foundB = registry_.Find(0xB);
            REQUIRE(foundB != nullptr);
            CHECK(foundB->GetTypeId() == 0xB);
            CHECK(foundB->GetName() == "type_B");
            CHECK(foundB->GetNamespace().ToString() == "some::scope");
        }
    }
}
