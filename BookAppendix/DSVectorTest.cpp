//
// Created by Deuce Palmer on 2/20/22.
//
#include "catch.hpp"
#include "DSVector.h"
#include <iostream>
TEST_CASE("DSVector class", "[DSVector]"){
    DSString str("integers");
    DSVector<int> ints(str);
    for (int i=0; i<9; i++){
        ints.push_back(i);
    }
    DSString ss("2");
    DSVector<DSString> dstrs(ss);
    DSString one("hi");
    dstrs.push_back(one);
    DSString two("hey");
    dstrs.push_back(two);
    DSString tre("hello");
    dstrs.push_back(tre);
    DSString four("bye");
    dstrs.push_back(four);
    DSString fi("goodbye");
    dstrs.push_back(fi);

    SECTION("Constructors"){
        DSString name("stringvector");
        DSVector<int> numbers(ints);
        DSVector<DSString> wrds;
        DSVector<DSString> strings(name);
        REQUIRE(numbers.getSize() == 9);
        REQUIRE(wrds.getSize() == 0);
        REQUIRE(wrds.getCapacity() == 10);
        REQUIRE(numbers.getCapacity() == 10);
        REQUIRE(strcmp(strings.getName().c_str(), "stringvector") == 0);
    }
    SECTION("Assignment Operator"){
        DSVector<int> cpy;
        cpy = ints;
        DSVector<DSString> scpy;
        scpy = dstrs;
        REQUIRE(cpy.getSize() == 9);
        REQUIRE(cpy.getCapacity() == 10);
        REQUIRE(strcmp(cpy.getName().c_str(), "integers") == 0);
        REQUIRE(scpy.getSize() == 5);
        REQUIRE(scpy.getCapacity() == 10);
    }
    SECTION("Subscript Operator"){
        REQUIRE(ints[0] == 0);
        REQUIRE(ints[2] == 2);
        REQUIRE(ints[4] == 4);
        REQUIRE(ints[6] == 6);
        int y=769;
        ints[9] = y;
        REQUIRE(ints[9] == 769);
    }
    SECTION("At Operator"){
        REQUIRE(ints.at(0) == 0);
        REQUIRE(ints.at(2) == 2);
        REQUIRE(ints.at(4) == 4);
        REQUIRE(dstrs.at(1) == two);
        REQUIRE(dstrs.at(2) == tre);
    }
    SECTION("Push_back"){
        int i = 27;
        ints.push_back(i);
        i++;
        ints.push_back(i);
        ints.push_back(i);
        i++;
        ints.push_back(i);
        REQUIRE(ints.getSize() == 13);
        REQUIRE(ints[9] == 27);
        REQUIRE(ints[10] == 28);
        REQUIRE(ints[12] == 29);
        REQUIRE(ints.getCapacity() == 20);
    }
    SECTION("Pop_back"){
        REQUIRE(dstrs.pop_back() == fi);
        REQUIRE(dstrs.pop_back() == four);
        REQUIRE(dstrs.pop_back() == tre);
        REQUIRE(dstrs.pop_back() == two);
        REQUIRE(dstrs.getSize() == 1);
    }
    SECTION("Resize"){
        DSVector<char> vec;
        REQUIRE(vec.getCapacity() == 10);
        vec.resize();
        REQUIRE(vec.getCapacity() == 20);
        ints.resize();
        REQUIRE(ints.getCapacity() == 20);
        dstrs.resize();
        REQUIRE(dstrs.getCapacity() == 20);
        vec.resize();
        REQUIRE(vec.getCapacity() == 40);
    }
    SECTION("Remove"){
        ints.remove(0);
        REQUIRE(ints.getSize() == 8);
        ints.remove(3);
        REQUIRE(ints[4] == 6);
        REQUIRE(ints[0] == 1);
        ints.remove(2);
        ints.remove(1);
        REQUIRE(ints[0] == 1);
        REQUIRE(ints.getSize() == 5);
    }
    SECTION("Search"){
        int ind = 1;
        int i = ints.search(ind);
        ind++;
        REQUIRE(ints[i] == 1);
        i = ints.search(ind);
        ind++;
        REQUIRE(ints[i] == 2);
        i = ints.search(ind);
        ind++;
        REQUIRE(ints[i] == 3);
        i = ints.search(ind);
        REQUIRE(ints[i] == 4);
        int x = 23043;
        REQUIRE(ints.search(x) == -1);
    }
    SECTION("Search 2.0"){
        DSString p("+-?!");
        DSString a("hi");
        int i = dstrs.search(a, p);
        REQUIRE(dstrs[i] == a);
        DSString b("hello");
        i = dstrs.search(b, p);
        REQUIRE(dstrs[i] == b);
        DSString c("hey");
        i = dstrs.search(c, p);
        REQUIRE(dstrs[i] == c);
        DSString d("bye");
        i = dstrs.search(d, p);
        REQUIRE(dstrs[i] == d);
        DSString x("palmer");
        REQUIRE(dstrs.search(x) == -1);
    }
    SECTION("Sort"){
        dstrs.sort();
        REQUIRE(dstrs[0] == four);
        REQUIRE(dstrs[1] == fi);
        REQUIRE(dstrs[2] == tre);
        REQUIRE(dstrs[3] == two);
        REQUIRE(dstrs[4] == one);
    }
    SECTION("Iterator"){
        REQUIRE(ints.get_next() == 0);
        REQUIRE(ints.get_next() == 1);
        REQUIRE(ints.get_next() == 2);
        ints.get_next();ints.get_next(); ints.get_next(); ints.get_next(); ints.get_next(); ints.get_next();
        REQUIRE(ints.has_next() == false);
        ints.reset_iterator();
        REQUIRE(ints.get_next() == 0);
    }
    SECTION("Compare"){
        DSString p("");
        DSString a("hi");
        DSString b("hey");
        DSString c("bye");
        DSVector<int> aa(a);
        DSVector<int> bb(b);
        DSVector<int> cc(c);
        DSVector<DSVector<int>> integ;
        integ.push_back(aa);
        integ.push_back(bb);
        integ.push_back(cc);
        dstrs.compare(integ, p);
        REQUIRE(integ[0][0] == 2);
        REQUIRE(integ[1][0] == 2);
        REQUIRE(integ[2][0] == 2);
        REQUIRE(integ[0].getCapacity() == 10);
        REQUIRE(integ[1].getSize() == 1);
    }
}
