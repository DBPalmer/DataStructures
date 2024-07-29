#include "catch.hpp"
#include "DSString.h"
#include <iostream>

TEST_CASE("DSString class", "[DSString]"){
    DSString a("hey");
    DSString b("yo");
    DSString c("hello");
    DSString aa("hey");
    DSString bb("");
    DSString cc("aapl");

    SECTION("Constructors") {
        DSString val("hi");
        REQUIRE(val == "hi");
        DSString name("Deuce Palmer");
        REQUIRE(name == DSString("Deuce Palmer"));
        DSString test(name.c_str());
        REQUIRE(test == "Deuce Palmer");
        DSString str(b.c_str());
        REQUIRE(str == b);
    }
    SECTION("Assignment Operators") {
        DSString wrd("hello world");
        DSString cpy = wrd;
        REQUIRE(cpy == "hello world");
        cpy = "hey";
        REQUIRE(cpy == "hey");
        REQUIRE(cpy == a);
        DSString str = c;
        REQUIRE(str == "hello");
        wrd = str;
        REQUIRE(wrd == "hello");
    }
    SECTION("Addition Operators") {
        DSString d = a + b;
        REQUIRE(d == "heyyo");
        DSString e = b + c;
        REQUIRE(e == "yohello");
        DSString wrd("hey");
        DSString word("hi");
        DSString f = word + wrd;
        REQUIRE(f == "hihey");
        DSString g = f + e;
        REQUIRE(g == "hiheyyohello");
    }
    SECTION("Equality Operators") {
        REQUIRE(a == "hey");
        REQUIRE(aa == DSString("hey"));
        REQUIRE(bb == "");
        DSString another("this is monotonous");
        REQUIRE(another == "this is monotonous");
        REQUIRE(a == aa);
    }
    SECTION("Greater Than") {
        REQUIRE(a > cc);
        REQUIRE(cc > bb);
        REQUIRE(aa > bb);
        REQUIRE(aa > cc);
        REQUIRE(c > cc);
    }
    SECTION("Subscript Operators") {
        DSString s("hello, my name is Deuce");
        REQUIRE(s[0] == 'h');
        REQUIRE(s[1] == 'e');
        REQUIRE(s[5] == ',');
        REQUIRE(a[2] == 'y');
        REQUIRE(a[2] == b[0]);
    }
    SECTION("Get Length") {
        DSString ten("iiiiiiiiii");
        REQUIRE(ten.getLength() == 10);
        REQUIRE(b.getLength() == 2);
        REQUIRE(cc.getLength() == 4);
        REQUIRE(c.getLength() == 5);
        REQUIRE(aa.getLength() == 3);
    }
    SECTION("Substring") {
        REQUIRE(c.substring(0,1) == "h");
        REQUIRE(c.substring(2, 3) == "llo");
        DSString str("I like puppies");
        REQUIRE(str.substring(1,5) == " like");
        REQUIRE(str.substring(4,3) == "ke ");
        REQUIRE(str.substring(5,7) == "e puppi");
    }
    SECTION("Number of Words") {
        DSString sentence("my name is Deuce");
        DSString sentence2("my name is Deuce Palmer and I am 20 years old");
        DSString sentence3("my name is Deuce Palmer and I am 20 years old and i am a cs minor");
        REQUIRE(sentence.numberOfWords() == 4);
        REQUIRE(sentence2.numberOfWords() == 11);
        REQUIRE(sentence3.numberOfWords() == 17);
        REQUIRE(a.numberOfWords() == 1);
    }
    SECTION("Parse") {
        DSString sentence("my name is Deuce Palmer and I am 20 years old and i am a cs minor");
        DSString sent2("I am 20 years old and i am a cs minor");
        REQUIRE(sentence.parse(9) == sent2.parse(3));
        REQUIRE(sentence.parse(10) == sent2.parse(4));
        REQUIRE(sentence.parse(11) == sent2.parse(5));
        REQUIRE(sentence.parse(8) == sent2.parse(2));
    }
}

