#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include "dynamic_array/dynamic_array.hpp"

// [10, 10, 10, 10, 10]
TEST_CASE("Constructor with size and value") {
    DynamicArray arr(5, 10);
    CHECK(arr.Size() == 5);
    CHECK(arr.Capacity() == 5);
    for (int i = 0; i < arr.Size(); ++i) {
        CHECK(arr[i] == 10);
    }
}

TEST_CASE("Constructor with initializer_list") {
    DynamicArray arr = {1, 2, 3, 4, 5};
    CHECK(arr.Size() == 5);
    CHECK(arr.Capacity() == 5);
    for (int i = 0; i < arr.Size(); ++i) {
        CHECK(arr[i] == i + 1);
    }
}

TEST_CASE("Size and Capacity") {
    DynamicArray arr(3, 0);
    CHECK(arr.Size() == 3);
    CHECK(arr.Capacity() >= 3);
}

// [] -> [10, 20] -> [10]
TEST_CASE("Push_back and pop_back") {
    DynamicArray arr;
    arr.push_back(10);
    arr.push_back(20);
    CHECK(arr.Size() == 2);
    CHECK(arr[0] == 10);
    CHECK(arr[1] == 20);
    arr.pop_back();
    CHECK(arr.Size() == 1);
    CHECK(arr[0] == 10);
}

TEST_CASE("Resize") {
    DynamicArray arr = {1, 2, 3};
    arr.resize(5);
    CHECK(arr.Size() == 5);
    CHECK(arr[3] == 0);
    CHECK(arr[4] == 0);
    arr.resize(2);
    CHECK(arr.Size() == 2);
}

//[1, 2, 3] - > [7, 7, 7, 7, 7]
TEST_CASE("Assign") {
    DynamicArray arr = {1, 2, 3};
    arr.assign(5, 7);
    CHECK(arr.Size() == 5);
    CHECK(arr[0] == 7);
    CHECK(arr[1] == 7);
    CHECK(arr[2] == 7);
    CHECK(arr[3] == 7);
    CHECK(arr[4] == 7);
}

//[1, 2, 3] -> [1, 10, 2, 3]
TEST_CASE("Insert") {
    DynamicArray arr = {1, 2, 3};
    arr.insert(1, 10);
    CHECK(arr.Size() == 4);
    CHECK(arr[1] == 10);
    CHECK(arr[2] == 2);
}

TEST_CASE("Erase") {
    DynamicArray arr = {1, 2, 3, 4};
    arr.erase(2);
    CHECK(arr.Size() == 3);
    CHECK(arr[2] == 4);
}

TEST_CASE("Clear") {
    DynamicArray arr = {1, 2, 3, 4};
    arr.clear();
    CHECK(arr.Size() == 0);
    CHECK(arr.empty() == true);
}

TEST_CASE("Equality operators") {
    DynamicArray arr1 = {1, 2, 3};
    DynamicArray arr2 = {1, 2, 3};
    DynamicArray arr3 = {4, 5, 6};
    CHECK(arr1 == arr2);
    CHECK(arr1 != arr3);
}

TEST_CASE("At operator") {
    DynamicArray arr = {1, 2, 3};
    CHECK(arr.at(0) == 1);
    CHECK(arr.at(1) == 2);
    CHECK(arr.at(2) == 3);
}

TEST_CASE("Indexing operator") {
    DynamicArray arr = {1, 2, 3};
    CHECK(arr[0] == 1);
    CHECK(arr[1] == 2);
    CHECK(arr[2] == 3);
}

TEST_CASE("Swap") {
    DynamicArray arr1 = {1, 2, 3};
    DynamicArray arr2 = {4, 5, 6};
    arr1.swap(arr2);
    CHECK(arr1[0] == 4);
    CHECK(arr2[0] == 1);
}

TEST_CASE("Empty check") {
    DynamicArray arr;
    CHECK(arr.empty() == true);
    arr.push_back(10);
    CHECK(arr.empty() == false);
}

//вставка за пределы массива
TEST_CASE("Insert out of bounds"){
    DynamicArray arr = {1, 1, 1};
    CHECK_THROWS_AS(arr.insert(5, 99), std::out_of_range);
}

//проверка, что capacity не уменьшается
TEST_CASE("Resize to smaller size") {
    DynamicArray arr;
    arr.resize(10);
    arr.resize(5);
    CHECK(arr.Size() == 5);
    CHECK(arr.Capacity() >= 10);
}

//при увеличении массива, новая выделенная память должна заполняться нулями
TEST_CASE("Resize to larger size") {
    DynamicArray arr;
    arr.resize(10);
    CHECK(arr.Size() == 10);
    CHECK(arr.Capacity() >= 10);
    for (int i = 0; i < 10; ++i) {
        CHECK(arr[i] == 0);
    }
}

TEST_CASE("Insert into empty array") {
    DynamicArray arr;
    arr.insert(0, 42);
    CHECK(arr.Size() == 1);
    CHECK(arr[0] == 42);
}

TEST_CASE("Resize -> Assign -> Insert") {
    DynamicArray arr;
    arr.resize(3); // [0, 0, 0]
    CHECK(arr.Size() == 3);
    arr.assign(5, 7); // [7, 7, 7, 7, 7]
    CHECK(arr.Size() == 5);
    arr.insert(2, 99); // [7, 7, 99, 7, 7, 7]
    CHECK(arr.Size() == 6);
    arr.resize(10); // [7, 7, 99, 7, 7, 7, 0, 0, 0, 0]
    CHECK(arr.Size() == 10);
    CHECK(arr[2] == 99);
    CHECK(arr[6] == 0);
}


