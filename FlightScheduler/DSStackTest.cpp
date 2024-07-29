#include "catch.hpp"
#include "DSLinkedList.h"
#include "DSStack.h"

TEST_CASE("DSStack class", "[DSStack]"){
    DSStack<int> stack;
    DSStack<int> stck;
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    stck.push(a);
    stck.push(b);
    stck.push(c);
    stck.push(d);
    SECTION("Push"){
        stack.push(a);
        REQUIRE(stack.getList().getHead().data == a);
        REQUIRE(stack.getList().getEnd().data == a);
        stack.push(b);
        REQUIRE(stack.getList().getEnd().data == b);
        stack.push(c);
        REQUIRE(stack.getList().getEnd().data == c);
        stack.push(stack.getList().getEnd().data);
        REQUIRE(stack.getList().getEnd().data == c);
    }
    SECTION("Peek"){
        REQUIRE(&stack.peek() == nullptr);
        REQUIRE(stck.peek() == d);
        DSStack<int> stack3;
        DSStack<int> stack4;
        DSStack<int> stk;
        stack3.push(a);
        stack4.push(c);
        stk.push(a);
        stk.push(b);
        REQUIRE(stack3.peek() == a);
        REQUIRE(stack4.peek() == c);
        REQUIRE(stk.peek() == b);
    }
    SECTION("Pop"){
        stack.pop();
        REQUIRE(&stack.peek() == nullptr);
        stck.pop();
        REQUIRE(stck.peek() == c);
        stck.pop();
        REQUIRE(stck.peek() == b);
        stck.pop();
        REQUIRE(stck.peek() == a);
        stck.pop();
        REQUIRE(&stck.peek() == nullptr);
    }
    SECTION("Is Empty"){
        REQUIRE(stack.is_empty() == true);
        stck.pop();
        REQUIRE(stck.is_empty()== false);
        stck.pop();
        REQUIRE(stck.is_empty() == false);
        stck.pop();
        REQUIRE(stck.is_empty() == false);
        stck.pop();
        REQUIRE(stck.is_empty() == true);
    }
    SECTION("Search"){
        int z = 17;
        int q =9;
        REQUIRE(stck.search(z) == false);
        REQUIRE(stck.search(q) == false);
        REQUIRE(stck.search(a) == true);
        REQUIRE(stck.search(b) == true);
        REQUIRE(stck.search(c) == true);
    }
}