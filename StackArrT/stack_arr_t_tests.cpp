#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <initializer_list>
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include "stack_arr_t/stack_arr_t.hpp"

TEST_CASE_TEMPLATE("Testing StackArrT with different types", T, int, float, double, long long) {
    SUBCASE("Default Constructor") {
        StackArrT<T> stack;
        CHECK(stack.empty());
        CHECK(stack.size() == 0);
    }

    SUBCASE("Push and Pop") {
        StackArrT<T> stack;
        stack.push(static_cast<T>(10));
        CHECK(stack.top() == static_cast<T>(10));
        stack.push(static_cast<T>(20));
        CHECK(stack.top() == static_cast<T>(20));
        stack.pop();
        CHECK(stack.top() == static_cast<T>(10));
    }

    SUBCASE("Initializer List Constructor") {
        StackArrT<T> stack = {static_cast<T>(1), static_cast<T>(2), static_cast<T>(3)};
        CHECK(stack.size() == 3);
        CHECK(stack.top() == static_cast<T>(3));
    }

    SUBCASE("Copy Constructor") {
        StackArrT<T> stack = {static_cast<T>(1), static_cast<T>(2), static_cast<T>(3)};
        StackArrT<T> stack2(stack);
        CHECK(stack2 == stack);
    }

    SUBCASE("Move Constructor") {
        StackArrT<T> stack = {static_cast<T>(1), static_cast<T>(2), static_cast<T>(3)};
        StackArrT<T> stack2(std::move(stack));
        CHECK(stack2.size() == 3);
        CHECK(stack.empty());
    }

    SUBCASE("Assignment Operator") {
        StackArrT<T> stack = {static_cast<T>(1), static_cast<T>(2), static_cast<T>(3)};
        StackArrT<T> stack2;
        stack2 = stack;
        CHECK(stack2 == stack);
    }

    SUBCASE("Move Assignment Operator") {
        StackArrT<T> stack = {static_cast<T>(1), static_cast<T>(2), static_cast<T>(3)};
        StackArrT<T> stack2;
        stack2 = std::move(stack);
        CHECK(stack2.size() == 3);
        CHECK(stack.empty());
    }

    SUBCASE("Swap") {
        StackArrT<T> stack1 = {static_cast<T>(1), static_cast<T>(2), static_cast<T>(3)};
        StackArrT<T> stack2 = {static_cast<T>(4), static_cast<T>(5)};
        stack1.swap(stack2);
        CHECK(stack1.size() == 2);
        CHECK(stack2.size() == 3);
    }

    SUBCASE("Merge") {
        StackArrT<T> stack1 = {static_cast<T>(1), static_cast<T>(2), static_cast<T>(3)};
        StackArrT<T> stack2 = {static_cast<T>(4), static_cast<T>(5)};
        stack1.merge(stack2);
        CHECK(stack1.size() == 5);
        CHECK(stack1.top() == static_cast<T>(5));
        CHECK(stack2.empty());
    }

    SUBCASE("Empty and Size") {
        StackArrT<T> stack;
        CHECK(stack.empty());
        stack.push(static_cast<T>(1));
        CHECK(stack.size() == 1);
        CHECK(!stack.empty());
    }

    SUBCASE("Equality and Inequality") {
        StackArrT<T> stack1 = {static_cast<T>(1), static_cast<T>(2), static_cast<T>(3)};
        StackArrT<T> stack2 = {static_cast<T>(1), static_cast<T>(2), static_cast<T>(3)};
        StackArrT<T> stack3 = {static_cast<T>(4), static_cast<T>(5)};
        CHECK(stack1 == stack2);
        CHECK(stack1 != stack3);
    }

    SUBCASE("Top on Empty Stack") {
        StackArrT<T> stack;
        CHECK_THROWS_AS(stack.top(), std::out_of_range);
    }
}