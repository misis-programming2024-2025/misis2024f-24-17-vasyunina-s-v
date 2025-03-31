#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <initializer_list>
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include "stack_lst_t/stack_lst_t.hpp"


 TEST_CASE("StackLstT - Basic Operations") {
     StackLstT<int> stack;
     
     SUBCASE("Default constructor creates empty stack") {
         CHECK(stack.empty());
         CHECK(stack.size() == 0);
     }
 
     SUBCASE("Push and top") {
         stack.push(10);
         CHECK(stack.top() == 10);
         CHECK(stack.size() == 1);
         
         stack.push(20);
         CHECK(stack.top() == 20);
         CHECK(stack.size() == 2);
     }
 
     SUBCASE("Pop") {
         stack.push(10);
         stack.push(20);
         
         stack.pop();
         CHECK(stack.top() == 10);
         CHECK(stack.size() == 1);
         
         stack.pop();
         CHECK(stack.empty());
     }
 
     SUBCASE("Pop on empty stack throws") {
         CHECK_THROWS_AS(stack.pop(), std::out_of_range);
     }
 
     SUBCASE("Top on empty stack throws") {
         CHECK_THROWS_AS(stack.top(), std::out_of_range);
     }
 }
 
 TEST_CASE("StackLstT - Constructors") {
     SUBCASE("Initializer list constructor") {
         StackLstT<int> stack{1, 2, 3};
         CHECK(stack.top() == 3);
         stack.pop();
         CHECK(stack.top() == 2);
     }
 
     SUBCASE("Copy constructor") {
         StackLstT<int> original{1, 2, 3};
         StackLstT<int> copy(original);
         
         CHECK(copy.top() == 3);
         original.pop();
         CHECK(copy.top() == 3); 
     }
 
     SUBCASE("Move constructor") {
         StackLstT<int> original{1, 2, 3};
         StackLstT<int> moved(std::move(original));
         
         CHECK(moved.top() == 3);
         CHECK(original.empty());
     }
 }
 
 TEST_CASE("StackLstT - Assignment Operators") {
     SUBCASE("Copy assignment") {
         StackLstT<int> original{1, 2, 3};
         StackLstT<int> copy;
         copy = original;
         
         CHECK(copy.top() == 3);
         original.pop();
         CHECK(copy.top() == 3);
     }
 
     SUBCASE("Move assignment") {
         StackLstT<int> original{1, 2, 3};
         StackLstT<int> moved;
         moved = std::move(original);
         
         CHECK(moved.top() == 3);
         CHECK(original.empty());
     }
 }
 
 TEST_CASE("StackLstT - Merge Operation") {
     SUBCASE("Merge non-empty stacks") {
         StackLstT<int> stack1{1, 2};
         StackLstT<int> stack2{3, 4};
         
         stack1.merge(stack2);
         
         CHECK(stack1.size() == 4);
         CHECK(stack2.empty());
         
         CHECK(stack1.top() == 4);
         stack1.pop();
         CHECK(stack1.top() == 3);
     }
 
     SUBCASE("Merge with empty stack") {
         StackLstT<int> stack1{1, 2};
         StackLstT<int> stack2;
         
         stack1.merge(stack2);
         CHECK(stack1.size() == 2);
         CHECK(stack2.empty());
     }
 
     SUBCASE("Merge empty with non-empty") {
         StackLstT<int> stack1;
         StackLstT<int> stack2{1, 2};
         
         stack1.merge(stack2);
         CHECK(stack1.size() == 2);
         CHECK(stack2.empty());
     }
 
     SUBCASE("Self-merge does nothing") {
         StackLstT<int> stack{1, 2};
         stack.merge(stack); 
         
         CHECK(stack.size() == 2);
         CHECK(stack.top() == 2);
     }
 }
 
 TEST_CASE("StackLstT - Comparison Operators") {
     SUBCASE("Equal stacks") {
         StackLstT<int> stack1{1, 2, 3};
         StackLstT<int> stack2{1, 2, 3};
         CHECK(stack1 == stack2);
         CHECK_FALSE(stack1 != stack2);
     }
 
     SUBCASE("Different stacks") {
         StackLstT<int> stack1{1, 2, 3};
         StackLstT<int> stack2{1, 2};
         CHECK(stack1 != stack2);
         CHECK_FALSE(stack1 == stack2);
     }
 }
 
 TEST_CASE("StackLstT - Edge Cases") {
     SUBCASE("Large stack") {
         StackLstT<int> stack;
         for (int i = 0; i < 10000; ++i) {
             stack.push(i);
         }
         CHECK(stack.size() == 10000);
         CHECK(stack.top() == 9999);
     }
 
     SUBCASE("Stack with different types") {
         StackLstT<std::string> stack;
         stack.push("test");
         CHECK(stack.top() == "test");
     }
 }