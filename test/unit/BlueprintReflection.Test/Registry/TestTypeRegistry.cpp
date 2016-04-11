#include <catch/catch.hpp>

#include "BlueprintReflection/Registry/TypeRegistry.hpp"
#include "BlueprintReflection/Type/Type.hpp"
#include "BlueprintReflection/Visitor/TypeVisitor.hpp"

#include <unordered_set>

using namespace blueprint::reflection;

struct FakeType : public Type
{
    virtual void Accept(TypeVisitor&) const override {}
};

struct TypeRegistryFixture
{
    template<typename T, typename... Args>
    std::unique_ptr<T> CreateType(uint64_t typeId, const std::string& typeName, const std::string& typeNamespace, Args&&... args)
    {
        auto type = std::make_unique<T>(std::forward<Args>(args)...);

        type->SetTypeId(typeId);
        type->SetName(typeName);
        type->SetNamespace(typeNamespace);

        return type;
    }

    std::unique_ptr<Type> CreateTypeA()
    {
        return CreateType<FakeType>(0xA, "type_A", "");
    }

    std::unique_ptr<Type> CreateTypeB()
    {
        return CreateType<FakeType>(0xB, "type_B", "some::scope");
    }

    template<typename T, typename... Args>
    void RegisterType(uint64_t typeId, const std::string& typeName, Args&&... args)
    {
        registry_.Register(CreateType<T>(typeId, typeName, std::forward<Args>(args)...));
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

TEST_CASE("TestTypeRegistry Singleton")
{
    CHECK(TypeRegistry::HasInstance() == false);
    CHECK(TypeRegistry::GetInstance() == nullptr);

    {
        TypeRegistry registry;

        CHECK(TypeRegistry::HasInstance() == true);
        CHECK(TypeRegistry::GetInstance() == &registry);
    }

    CHECK(TypeRegistry::HasInstance() == false);
    CHECK(TypeRegistry::GetInstance() == nullptr);
}

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

    SECTION("Accept")
    {
        struct FakeVisitor : public TypeVisitor
        {
            virtual void Visit(const ClassType& /*type*/) override {}
            virtual void Visit(const EnumType&  /*type*/) override {}

            virtual void Visit(const TypeRegistry& registry) override
            {
                visitedRegistry = &registry;
            }

            void FakeVisit(const Type* type)
            {
                visited.insert(type->GetTypeId());
            }

            std::unordered_set<uint64_t> visited;
            const TypeRegistry* visitedRegistry{nullptr};
        };

        struct FadeVisitedType : public Type
        {
            virtual void Accept(TypeVisitor& visitor) const
            {
                static_cast<FakeVisitor&>(visitor).FakeVisit(this);
            }
        };

        RegisterType<FadeVisitedType>(0xA, "fake_A", "");
        RegisterType<FadeVisitedType>(0xB, "fake_B", "");
        RegisterType<FadeVisitedType>(0xC, "fake_C", "");

        FakeVisitor visitor;
        registry_.Accept(visitor);

        CHECK(visitor.visitedRegistry == &registry_);

        REQUIRE(visitor.visited.size() == 3);
        CHECK(visitor.visited.find(0xA) != visitor.visited.end());
        CHECK(visitor.visited.find(0xB) != visitor.visited.end());
        CHECK(visitor.visited.find(0xC) != visitor.visited.end());
    }
}
