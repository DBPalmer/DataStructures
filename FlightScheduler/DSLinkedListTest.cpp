#include "catch.hpp"
#include "DSString.h"
#include "DSLinkedList.h"

TEST_CASE("DSLinkedList class", "[DSLinkedList]"){
    DSLinkedList<DSString> wrds;
    DSLinkedList<DSString> list;
    DSString a("front");
    DSString b("middle");
    DSString c("back");
    list.push_back(a);
    list.push_back(b);
    list.push_back(c);
    DSLinkedList<DSString> str;
    DSString aa("one");
    DSString bb("two");
    DSString cc("three");
    DSString dd("four");
    DSString ee("five");
    str.push_front(aa);
    str.push_front(bb);
    str.push_front(cc);
    str.push_front(dd);
    str.push_front(ee);
    SECTION("Constructor"){
        DSLinkedList<DSString> cpy(wrds);
        DSLinkedList<DSString> cpy2(list);
        REQUIRE(&wrds.getEnd() == nullptr);
        REQUIRE(&wrds.getHead() == nullptr);
        REQUIRE(&cpy.getEnd() == nullptr);
        REQUIRE(cpy2.getHead().data == a);
        REQUIRE(cpy2.getEnd().data == c);
    }
    SECTION("Assignment Operator"){
        DSLinkedList<DSString> lst;
        lst = list;
        REQUIRE(lst.getHead().data == a);
        REQUIRE(lst.getHead().next->data == b);
        REQUIRE(lst.getEnd().data == c);
        lst = wrds;
        REQUIRE(&lst.getEnd() == nullptr);
        REQUIRE(&lst.getHead() == nullptr);
    }
    SECTION("Push Back"){
        DSLinkedList<DSString> strs;
        DSString aa("one");
        DSString bb("two");
        DSString cc("three");
        DSString dd("four");
        DSString ee("five");
        strs.push_back(aa);
        strs.push_back(bb);
        strs.push_back(cc);
        strs.push_back(dd);
        strs.push_back(ee);
        REQUIRE(strs.getHead().data == aa);
        REQUIRE(strs.getHead().next->data == bb);
        REQUIRE(strs.getHead().next->next->data == cc);
        REQUIRE(strs.getEnd().prev->data == dd);
        REQUIRE(strs.getEnd().data == ee);
    }
    SECTION("Push Front"){
        REQUIRE(str.getHead().data == ee);
        REQUIRE(str.getHead().next->data == dd);
        REQUIRE(str.getHead().next->next->data == cc);
        REQUIRE(str.getEnd().prev->data == bb);
        REQUIRE(str.getEnd().data == aa);
    }
    SECTION("Remove Back"){
        str.remove_back();
        REQUIRE(str.getEnd().data == bb);
        str.remove_back();
        REQUIRE(str.getEnd().data == cc);
        str.remove_back();
        REQUIRE(str.getEnd().data == dd);
        str.remove_back();
        REQUIRE(str.getEnd().data == ee);
        str.remove_back();
        REQUIRE(&str.getEnd() == nullptr);
    }
    SECTION("Iterator Functions"){
        list.reset();
        REQUIRE(list.getElement().data == a);
        REQUIRE(list.hasElement() == true);
        list.getNext();
        REQUIRE(list.getElement().data == b);
        list.getNext();
        REQUIRE(list.getElement().data == c);
        list.getNext();
        REQUIRE(list.hasElement() == false);
    }
    SECTION("Search"){
        DSString w("hello");
        DSString q("hi");
        REQUIRE(list.search(w) == false);
        REQUIRE(list.search(b) == true);
        REQUIRE(list.search(a) == true);
        REQUIRE(str.search(aa) == true);
        REQUIRE(str.search(cc) == true);
    }
    SECTION("Find"){
        DSString s("dog");
        DSString x("cat");
        list.push_back(s);
        list.push_back(x);
        REQUIRE(list.find(a) == a);
        REQUIRE(list.find(b) == b);
        REQUIRE(list.find(c) == c);
        REQUIRE(list.find(x) == x);
        REQUIRE(list.find(s) == s);
    }
}