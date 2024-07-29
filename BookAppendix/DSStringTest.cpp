//
// Created by Deuce Palmer on 2/20/22.
//
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
        DSString vlue(val.c_str());
        REQUIRE(vlue == val);
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
        DSString wrd1("123");
        DSString wrd2("456");
        REQUIRE((wrd1+wrd2)=="123456");
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
    SECTION("Less Than") {
        REQUIRE(cc < a);
        REQUIRE(bb < cc);
        REQUIRE(bb < aa);
        REQUIRE(cc < aa);
        REQUIRE(cc < a);
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
    SECTION("c_str"){
        REQUIRE(strcmp(a.c_str(), "hey") == 0);
        REQUIRE(strcmp(b.c_str(), "yo") == 0);
        REQUIRE(strcmp(c.c_str(), "hello") == 0);
        REQUIRE(strcmp(cc.c_str(), "aapl") == 0);
        REQUIRE(strcmp(a.c_str(), aa.c_str()) == 0);
    }
    SECTION("Number of Words") {
        DSString sentence("my name is Deuce");
        DSString sentence2("my name is Deuce Palmer and I am 20 years old");
        DSString sentence3("my name is Deuce Palmer and I am 20 years old and i am a cs minor");
        REQUIRE(sentence.numberOfWords() == 4);
        REQUIRE(sentence2.numberOfWords() == 11);
        REQUIRE(sentence3.numberOfWords() == 17);
        REQUIRE(a.numberOfWords() == 1);
        REQUIRE(b.numberOfWords() == 1);
    }
    SECTION("Parse") {
        DSString sentence("my name is Deuce Palmer and I am 20 years old and i am a cs minor");
        DSString sent2("I am 20 years old and i am a cs minor");
        REQUIRE(sentence.parse(9) == sent2.parse(3));
        REQUIRE(sentence.parse(10) == sent2.parse(4));
        REQUIRE(sentence.parse(11) == sent2.parse(5));
        REQUIRE(sentence.parse(8) == sent2.parse(2));
        REQUIRE(sentence.parse(13) == sent2.parse(7));
    }
    SECTION("Parse 2.0") {
        DSString sentence("my n+-ame is! Deuce Pal-mer and I am 20 ye?ars old an,d i am a c@s minor");
        DSString punct("+-");
        REQUIRE(strcmp(sentence.pars(1, punct).c_str(), "n+-ame") == 0);
        REQUIRE(strcmp(sentence.pars(5, punct).c_str(), "and") == 0);
        REQUIRE(strcmp(sentence.pars(15, punct).c_str(), "cs") == 0);
        REQUIRE(strcmp(sentence.pars(9, punct).c_str(), "years") == 0);
        REQUIRE(strcmp(sentence.pars(11, punct).c_str(), "and") == 0);
    }
    SECTION("Get Punctuation") {
        DSString punct("+-");
        DSString punct2("hello!");
        DSString punct3("what??!!");
        DSString punct4("they're");
        DSString punct5("@deuce#!");
        REQUIRE(strcmp(punct.getPunct().c_str(), "+-") == 0);
        REQUIRE(strcmp(punct2.getPunct().c_str(), "!") == 0);
        REQUIRE(strcmp(punct3.getPunct().c_str(), "??!!") == 0);
        REQUIRE(strcmp(punct4.getPunct().c_str(), "'") == 0);
        REQUIRE(strcmp(punct5.getPunct().c_str(), "@#!") == 0);
    }
    SECTION("All Lower") {
        DSString a("HeLLo");
        a.all_Lower();
        REQUIRE(strcmp(a.c_str(), "hello") == 0);
        DSString b("DAD");
        b.all_Lower();
        REQUIRE(strcmp(b.c_str(), "dad") == 0);
        DSString c("MoM");
        c.all_Lower();
        REQUIRE(strcmp(c.c_str(), "mom") == 0);
        DSString d("WWeeEEeeEE");
        d.all_Lower();
        REQUIRE(strcmp(d.c_str(), "wweeeeeeee") == 0);
        DSString e("DoGG");
        e.all_Lower();
        REQUIRE(strcmp(e.c_str(), "dogg") == 0);
    }
}

