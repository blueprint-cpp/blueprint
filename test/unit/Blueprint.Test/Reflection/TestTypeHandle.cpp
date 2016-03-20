#include <catch/catch.hpp>

#include "Blueprint/Reflection/ClassType.hpp"
#include "Blueprint/Reflection/EnumType.hpp"
#include "Blueprint/Reflection/TypeHandle.hpp"
#include "Blueprint/Reflection/TypeRegistry.hpp"

TEST_CASE("TestTypeHandle")
{
    using namespace blueprint::reflection;

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

    SECTION("GetType")
    {
        auto typeA = std::make_unique<ClassType>();
        auto typeB = std::make_unique<EnumType>();

        typeA->SetTypeId(0xA);
        typeB->SetTypeId(0xB);

        TypeHandle handleA(0xA);
        TypeHandle handleB(0xB);

        SECTION("Returns null if not registered in the registry")
        {
            CHECK(handleA.Get() == nullptr);
            CHECK(handleB.Get() == nullptr);
        }

        SECTION("Returns types if properly registered in the registry")
        {
            auto addressA = typeA.get();
            auto addressB = typeB.get();

            TypeRegistry registry;

            registry.Register(std::move(typeA));
            registry.Register(std::move(typeB));

            CHECK(handleA.Get() == addressA);
            CHECK(handleB.Get() == addressB);
        }
    }
}
