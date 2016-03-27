#include <catch/catch.hpp>

#include "Blueprint/Reflection/Namespace.hpp"

TEST_CASE("TestNamespace")
{
    using namespace blueprint::reflection;

    SECTION("Construction")
    {
        std::hash<std::string> hash;

        SECTION("Default")
        {
            Namespace ns;

            CHECK(ns.IsGlobal() == true);
            CHECK(ns.GetDepth() == 0);
            CHECK(ns.GetCrc()   == 0);
            CHECK(ns.ToString() == "");
        }

        SECTION("Emptry string")
        {
            Namespace ns("");

            CHECK(ns.IsGlobal() == true);
            CHECK(ns.GetDepth() == 0);
            CHECK(ns.GetCrc()   == 0);
            CHECK(ns.ToString() == "");
        }

        SECTION("Single level namespace")
        {
            Namespace ns("foo");

            CHECK(ns.IsGlobal() == false);
            CHECK(ns.GetDepth() == 1);
            CHECK(ns.GetCrc()   == hash("foo"));
            CHECK(ns.ToString() == "foo");
        }

        SECTION("Multi level namespace")
        {
            Namespace ns("level_1::level_2::level_3");

            CHECK(ns.IsGlobal() == false);
            CHECK(ns.GetDepth() == 3);
            CHECK(ns.GetCrc()   == hash("level_1::level_2::level_3"));
            CHECK(ns.ToString() == "level_1::level_2::level_3");
        }
    }

    SECTION("Push")
    {
        Namespace global;

        Namespace a = global.Push("A");
        CHECK(a.ToString() == "A");

        Namespace abc = a.Push("B::C");
        CHECK(abc.ToString() == "A::B::C");
    }

    SECTION("Pop")
    {
        Namespace abc("A::B::C");

        Namespace ab = abc.Pop();
        CHECK(ab.ToString() == "A::B");

        Namespace a = ab.Pop();
        CHECK(a.ToString() == "A");

        Namespace global = a.Pop();
        CHECK(global.IsGlobal() == true);
        CHECK(global.ToString() == "");

        Namespace stillGlobal = global.Pop();
        CHECK(stillGlobal.IsGlobal() == true);
        CHECK(stillGlobal.ToString() == "");
    }
}
