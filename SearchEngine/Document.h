//
// Created by Deuce Palmer on 4/19/22.
//
//last edited: 4/28/2022
#ifndef INC_22S_FINAL_PROJ_DOCUMENT_H
#define INC_22S_FINAL_PROJ_DOCUMENT_H
#include <iostream>
using namespace std;
class Document {
private:
    string id;
    double score;
public:
    //rule of 3 doesn't apply since there is no need for a destructor, copy constructor, or an overloaded asg operator
    /**
     * constructors
     */
    Document();
    Document(string, double);
    Document(string, int, double, string);
    /**
     * getters
     */
    string getId();
    double getScore();
    /**
     * used for sorting
     */
    bool operator<(const Document&);
    /**
     * used for searching for terms in AND query operator and Word::search
     */
    bool operator==(const Document&);
};


#endif //INC_22S_FINAL_PROJ_DOCUMENT_H
