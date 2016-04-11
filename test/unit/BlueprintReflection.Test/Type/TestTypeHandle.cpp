#include <catch/catch.hpp>

#include "BlueprintReflection/Registry/TypeRegistry.hpp"
#include "BlueprintReflection/Type/ClassType.hpp"
#include "BlueprintReflection/Type/EnumType.hpp"
#include "BlueprintReflection/Type/TypeHandle.hpp"

using namespace blueprint::reflection;

namespace
{
    struct RegisteredTypes
    {
        RegisteredTypes()
        {
            auto typeA = std::make_unique<ClassType>();
            auto typeB = std::make_unique<EnumType>();

            typeA->SetTypeId(0xA);
            typeB->SetTypeId(0xB);

            addressA = typeA.get();
            addressB = typeB.get();

            registry.Register(std::move(typeA));
            registry.Register(std::move(typeB));
        }

        const Type* addressA{nullptr};
        const Type* addressB{nullptr};

        TypeRegistry registry;
    };
}

TEST_CASE("TestTypeHandle")
{
    SECTION("Construction")
    {
        SECTION("Default")
        {
            TypeHandle handle;

            CHECK(handle.GetId() == 0);
        }

        SECTION("With TypeId")
        {
            TypeHandle handle(0xA);

            CHECK(handle.GetId() == 0xA);
        }
    }

    SECTION("Comparison")
    {
        TypeHandle original(0xA);
        TypeHandle same(0xA);
        TypeHandle copy(original);
        TypeHandle different(0xB);

        SECTION("Equality")
        {
            CHECK((original == same) == true);
            CHECK((original == copy) == true);
            CHECK((original == different) == false);
        }

        SECTION("Inequality")
        {
            CHECK((original != same) == false);
            CHECK((original != copy) == false);
            CHECK((original != different) == true);
        }
    }

    SECTION("Validity")
    {
        TypeHandle handleA(0xA);
        TypeHandle handleB(0xB);

        SECTION("Invalid if type not registered")
        {
            const bool testA = handleA;
            const bool testB = handleB;

            CHECK(testA == false);
            CHECK(testB == false);
        }

        SECTION("Valid if type is registered")
        {
            RegisteredTypes types;

            const bool testA = handleA;
            const bool testB = handleB;

            CHECK(testA == true);
            CHECK(testB == true);
        }
    }

    SECTION("Get")
    {
        TypeHandle handleA(0xA);
        TypeHandle handleB(0xB);

        SECTION("Returns null if not registered in the registry")
        {
            CHECK(handleA.Get() == nullptr);
            CHECK(handleB.Get() == nullptr);
        }

        SECTION("Returns types if properly registered in the registry")
        {
            RegisteredTypes types;

            CHECK(handleA.Get() == types.addressA);
            CHECK(handleB.Get() == types.addressB);

            CHECK(handleA->GetTypeId() == 0xA);
            CHECK(handleB->GetTypeId() == 0xB);
        }
    }
}
