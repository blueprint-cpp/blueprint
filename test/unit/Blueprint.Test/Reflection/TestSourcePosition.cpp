#include <catch/catch.hpp>

#include "Blueprint/Reflection/SourcePosition.hpp"

TEST_CASE("TestSourcePosition")
{
    using namespace blueprint::reflection;

    SECTION("Construction")
    {
        SECTION("Default")
        {
            SourcePosition position;

            CHECK(position.GetLine() == 0);
            CHECK(position.GetColumn() == 0);
            CHECK(position.GetOffset() == 0);
        }

        SECTION("With Params")
        {
            SourcePosition positionA(1, 2, 3);

            CHECK(positionA.GetLine() == 1);
            CHECK(positionA.GetColumn() == 2);
            CHECK(positionA.GetOffset() == 3);

            SourcePosition positionB(4, 5, 6);

            CHECK(positionB.GetLine() == 4);
            CHECK(positionB.GetColumn() == 5);
            CHECK(positionB.GetOffset() == 6);
        }
    }

    SECTION("Comparison")
    {
        SourcePosition original(1, 2, 3);
        SourcePosition same(1, 2, 3);
        SourcePosition copy(original);
        SourcePosition different1(9, 2, 3);
        SourcePosition different2(1, 9, 3);
        SourcePosition different3(1, 2, 9);

        SECTION("Equality")
        {
            CHECK((original == same) == true);
            CHECK((original == copy) == true);
            CHECK((original == different1) == false);
            CHECK((original == different2) == false);
            CHECK((original == different3) == false);
        }

        SECTION("Inequality")
        {
            CHECK((original != same) == false);
            CHECK((original != copy) == false);
            CHECK((original != different1) == true);
            CHECK((original != different2) == true);
            CHECK((original != different3) == true);
        }
    }

    SECTION("Accessors")
    {
        SourcePosition position;

        SECTION("Line")
        {
            position.SetLine(11);
            CHECK(position.GetLine() == 11);

            position.SetLine(22);
            CHECK(position.GetLine() == 22);
        }

        SECTION("Column")
        {
            position.SetColumn(11);
            CHECK(position.GetColumn() == 11);

            position.SetColumn(22);
            CHECK(position.GetColumn() == 22);
        }

        SECTION("Offset")
        {
            position.SetOffset(11);
            CHECK(position.GetOffset() == 11);

            position.SetOffset(22);
            CHECK(position.GetOffset() == 22);
        }
    }

    SECTION("ToString")
    {
        SourcePosition positionA(1, 2, 3);
        CHECK(positionA.ToString() == "(1:2:3)");

        SourcePosition positionB(4, 5, 6);
        CHECK(positionB.ToString() == "(4:5:6)");
    }
}
