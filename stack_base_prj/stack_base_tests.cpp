#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack_arr_t.hpp"
#include "stack_lst_t.hpp"

TEST_CASE("Testing StackArrT basic operations") {
    StackArrT<int> stack;

    SUBCASE("Empty stack") {
        CHECK(stack.empty());
        CHECK(stack.size() == 0);
        
        std::ostringstream oss;
        stack.printToStream(oss);
        CHECK(oss.str() == "");
    }

    SUBCASE("Push and top") {
        stack.push(10);
        CHECK(stack.top() == 10);
        stack.push(20);
        CHECK(stack.top() == 20);
        
        std::ostringstream oss;
        stack.printToStream(oss);
        CHECK(oss.str() == "10 20");
    }

    SUBCASE("Pop") {
        stack.push(1);
        stack.push(2);
        stack.pop();
        CHECK(stack.top() == 1);
        
        std::ostringstream oss;
        stack.printToStream(oss);
        CHECK(oss.str() == "1");
    }
}

TEST_CASE("Testing StackLstT basic operations") {
    StackLstT<int> stack;

    SUBCASE("Empty stack") {
        CHECK(stack.empty());
        CHECK(stack.size() == 0);
        
        std::ostringstream oss;
        stack.printToStream(oss);
        CHECK(oss.str() == "");
    }

    SUBCASE("Push and top") {
        stack.push(10);
        CHECK(stack.top() == 10);
        stack.push(20);
        CHECK(stack.top() == 20);
        
        std::ostringstream oss;
        stack.printToStream(oss);
        CHECK(oss.str() == "20 10");
    }

    SUBCASE("Pop") {
        stack.push(1);
        stack.push(2);
        stack.pop();
        CHECK(stack.top() == 1);
        
        std::ostringstream oss;
        stack.printToStream(oss);
        CHECK(oss.str() == "1");
    }
}

TEST_CASE("Testing StackArrT merge") {
    StackArrT<int> stack1;
    stack1.push(1);
    stack1.push(2);

    StackArrT<int> stack2;
    stack2.push(3);
    stack2.push(4);

    stack1.merge(stack2);

    CHECK(stack1.size() == 4);
    
    std::ostringstream oss;
    stack1.printToStream(oss);
    CHECK(oss.str() == "1 2 3 4");
}

TEST_CASE("Testing StackLstT merge") {
    StackLstT<int> stack1;
    stack1.push(1);
    stack1.push(2);

    StackLstT<int> stack2;
    stack2.push(3);
    stack2.push(4);

    stack1.merge(stack2);

    CHECK(stack1.size() == 4);
    
    std::ostringstream oss;
    stack1.printToStream(oss);
    CHECK(oss.str() == "2 1 4 3");
}

TEST_CASE("Testing StackArrT output stream") {
    StackArrT<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::ostringstream oss;
    oss << stack;
    CHECK(oss.str() == "1 2 3");
}

TEST_CASE("Testing StackLstT output stream") {
    StackLstT<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::ostringstream oss;
    oss << stack;
    CHECK(oss.str() == "3 2 1");
}