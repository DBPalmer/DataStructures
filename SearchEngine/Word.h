//
// Created by Deuce Palmer on 4/14/22.
//
//last edit on: 5/02/22
#ifndef INC_22S_FINAL_PROJ_WORD_H
#define INC_22S_FINAL_PROJ_WORD_H
#include <string>
#include <vector>
#include <algorithm>
#include "Document.h"
using namespace std;

class Word {
private:
    string word;
    vector<Document> documents;//all the documents in which the word was found
public:
    /**
     * constructors
     */
    Word();
    Word(string&);
    Word(const Word&);
    /**
     * destructor
     */
    ~Word();
    /**
     * overloaded asg op
     */
    Word& operator=(const Word&);
    /**
     * equals op
     */
    bool operator==(const Word&);
    /**
     * less than op. Greater than not needed since never used in AVLTree
     */
    bool operator<(const Word&);
    /**
     * pushes a string to documents
     */
    void push_back(Document&);
    /**
     * getters
     */
    string getWord();
    vector<Document> getDoc();
    /**
     * searches for a doc in documents
     */
    bool search(Document&);
};


#endif //INC_22S_FINAL_PROJ_WORD_H
