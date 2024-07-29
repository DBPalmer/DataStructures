//
// Created by Deuce Palmer on 4/19/22.
//
//last edited: 5/02/2022
#include "Document.h"
Document::Document(){//empty
}
Document::Document(string s, double scre){//used when reading persistent index, since score is already calculated
    id = s;
    score = scre;
}
Document::Document(string s, int rnk, double spam, string dte){//calculates score and sets id
    id = s;
    int date = stoi(dte.substr(5,2));//date is used as well to further increase score for earlier published documents
    //seems like all the documents were published in 2018, so the substr only capture the month to be used
    score = rnk * spam * (12-date);
}
string Document::getId(){
    return id;
}
double Document::getScore() {
    return score;
}
bool Document::operator<(const Document& doc){
    return (score < doc.score);//compares score, used to sort
}
bool Document::operator==(const Document& doc){
    return (id == doc.id);//compares id, used to search
}