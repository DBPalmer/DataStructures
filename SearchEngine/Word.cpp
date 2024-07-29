//
// Created by Deuce Palmer on 4/14/22.
//
//last edit on: 5/02/22
#include "Word.h"
Word::Word(){//empty
}
Word::Word(string& s){
    word = s;
}
Word::Word(const Word& wrd){
    word = wrd.word;
    documents = wrd.documents;
}
Word::~Word(){//empty since its private variables have their own destructors
}
bool Word::operator==(const Word& wrd){
    //only compares the word itself, not the documents. Important for AVLTree comparisons
    return (word == wrd.word);
}
bool Word::operator<(const Word& wrd){
    //only compares the word itself, not the documents. Important for AVLTree comparisons
    return (word < wrd.word);
}
void Word::push_back(Document& s){
    documents.push_back(s);
}
string Word::getWord(){
    return word;
}
vector<Document> Word::getDoc(){
    return documents;
}
bool Word::search(Document& doc){
    if (std::find(documents.begin(), documents.end(), doc) == documents.end()){//if doc was not found
        return false;
    } else {//if doc was found
        return true;
    }
}