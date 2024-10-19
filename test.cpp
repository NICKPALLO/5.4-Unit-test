#include <iostream>

#include"my_list.h"

#include <catch2/catch_test_macros.hpp>

#include <cstdint>




TEST_CASE("First task")
{
    List list;
    list.PushBack(5);
    list.PushBack(10);
    SECTION("Empty")
    {
        INFO("list is not empty, something is wrong");
        CHECK(list.Empty() != true);
    }
    SECTION("SIZE")
    {
        INFO("Incorrect size");
        CHECK(list.Size() == 2);
    }
    list.Clear();
    SECTION("CLEAR")
    {
        INFO("After clear list is not empty");
        CHECK(list.Empty() == true);
    }
}

TEST_CASE("Second task")
{
    List list;
    list.PushBack(5);
    SECTION("PUSH_BACK")
    {
        INFO("Incorrect size");
        CHECK(list.Size() == 1);
    }
    list.PushFront(6);
    SECTION("PUSH_FRONT")
    {
        INFO("Incorrect size");
        CHECK(list.Size() == 2);
    }
    list.Clear();
    SECTION("POP_BACK")
    {
        INFO("The function pop_back doesn't work correctly");
        CHECK_THROWS(list.PopBack());
    }
    SECTION("POP_FRONT")
    {
        INFO("The function pop_front doesn't work correctly");
        CHECK_THROWS(list.PopFront());
    }
}