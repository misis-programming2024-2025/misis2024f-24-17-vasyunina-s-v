#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack_arr_t.hpp"
#include "stack_lst_t.hpp"

TEST_CASE("Testing StackArrT basic operations") {
    StackArrT<int> stack;

    SUBCASE("Empty stack") {
        CHECK(stack.empty());
        CHECK(stack.size() == 0);
    }

    SUBCASE("Push and top") {
        stack.push(10);
        CHECK(stack.top() == 10);
        stack.push(20);
        CHECK(stack.top() == 20);
    }

    SUBCASE("Pop") {
        stack.push(1);
        stack.push(2);
        stack.pop();
        CHECK(stack.top() == 1);
        stack.pop();
        CHECK(stack.empty());
    }
}

TEST_CASE("Testing StackLstT basic operations") {
    StackLstT<int> stack;

    SUBCASE("Empty stack") {
        CHECK(stack.empty());
        CHECK(stack.size() == 0);
    }

    SUBCASE("Push and top") {
        stack.push(10);
        CHECK(stack.top() == 10);
        stack.push(20);
        CHECK(stack.top() == 20);
    }

    SUBCASE("Pop") {
        stack.push(1);
        stack.push(2);
        stack.pop();
        CHECK(stack.top() == 1);
        stack.pop();
        CHECK(stack.empty());
    }
}

TEST_CASE("Testing StackArrT copy and move semantics") {
    StackArrT<int> stack1;
    stack1.push(1);
    stack1.push(2);

    SUBCASE("Copy constructor") {
        StackArrT<int> stack2(stack1);
        CHECK(stack2.top() == 2);
        CHECK(stack2.size() == 2);
    }

    SUBCASE("Move constructor") {
        StackArrT<int> stack3(std::move(stack1));
        CHECK(stack3.top() == 2);
        CHECK(stack1.empty());  // После перемещения исходный стек должен быть пуст
    }
}

TEST_CASE("Testing StackLstT copy and move semantics") {
    StackLstT<int> stack1;
    stack1.push(1);
    stack1.push(2);

    SUBCASE("Copy constructor") {
        StackLstT<int> stack2(stack1);
        CHECK(stack2.top() == 2);
        CHECK(stack2.size() == 2);
    }

    SUBCASE("Move constructor") {
        StackLstT<int> stack3(std::move(stack1));
        CHECK(stack3.top() == 2);
        CHECK(stack1.empty());  // После перемещения исходный стек должен быть пуст
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
    CHECK(stack1.top() == 4);
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
    CHECK(stack1.top() == 4);
}

TEST_CASE("Testing StackArrT swap") {
    StackArrT<int> stack1;
    stack1.push(1);
    stack1.push(2);

    StackArrT<int> stack2;
    stack2.push(3);

    stack1.swap(stack2);

    CHECK(stack1.size() == 1);
    CHECK(stack1.top() == 3);
    CHECK(stack2.size() == 2);
    CHECK(stack2.top() == 2);
}

TEST_CASE("Testing StackLstT swap") {
    StackLstT<int> stack1;
    stack1.push(1);
    stack1.push(2);

    StackLstT<int> stack2;
    stack2.push(3);

    stack1.swap(stack2);

    CHECK(stack1.size() == 1);
    CHECK(stack1.top() == 3);
    CHECK(stack2.size() == 2);
    CHECK(stack2.top() == 2);
}

TEST_CASE("Testing StackArrT output stream") {
    StackArrT<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::ostringstream oss;
    oss << stack;
    CHECK(oss.str() == "[1, 2, 3]");
}

TEST_CASE("Testing StackLstT output stream") {
    StackLstT<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::ostringstream oss;
    oss << stack;
    CHECK(oss.str() == "[1, 2, 3]");
}

TEST_CASE("Testing StackArrT and StackLstT comparison") {
    StackArrT<int> arrStack;
    arrStack.push(1);
    arrStack.push(2);

    StackLstT<int> listStack;
    listStack.push(1);
    listStack.push(2);

    CHECK(arrStack == listStack);  // Должен быть реализован operator==
    CHECK_FALSE(arrStack != listStack);
}

TEST_CASE("Testing StackArrT printToStream") {
    StackArrT<int> stack;
    
    SUBCASE("Empty stack") {
        std::ostringstream oss;
        stack.printToStream(oss);
        CHECK(oss.str() == "[]");
    }

    SUBCASE("Non-empty stack") {
        stack.push(1);
        stack.push(2);
        stack.push(3);

        std::ostringstream oss;
        stack.printToStream(oss);
        CHECK(oss.str() == "[1, 2, 3]");
    }
}

TEST_CASE("Testing StackLstT printToStream") {
    StackLstT<int> stack;
    
    SUBCASE("Empty stack") {
        std::ostringstream oss;
        stack.printToStream(oss);
        CHECK(oss.str() == "[]");
    }

    SUBCASE("Non-empty stack") {
        stack.push(1);
        stack.push(2);
        stack.push(3);

        std::ostringstream oss;
        stack.printToStream(oss);
        CHECK(oss.str() == "[1, 2, 3]");
    }
}

TEST_CASE("Testing operator<< for StackArrT") {
    StackArrT<int> stack;
    stack.push(10);
    stack.push(20);

    std::ostringstream oss;
    oss << stack;
    CHECK(oss.str() == "[10, 20]");
}

TEST_CASE("Testing operator<< for StackLstT") {
    StackLstT<int> stack;
    stack.push(30);
    stack.push(40);

    std::ostringstream oss;
    oss << stack;
    CHECK(oss.str() == "[30, 40]");
}

TEST_CASE("Testing StackArrT output after operations") {
    StackArrT<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    SUBCASE("After pop") {
        stack.pop();
        std::ostringstream oss;
        oss << stack;
        CHECK(oss.str() == "[1, 2]");
    }

    SUBCASE("After merge") {
        StackArrT<int> other;
        other.push(4);
        other.push(5);
        stack.merge(other);
        
        std::ostringstream oss;
        oss << stack;
        CHECK(oss.str() == "[1, 2, 3, 4, 5]");
    }
}