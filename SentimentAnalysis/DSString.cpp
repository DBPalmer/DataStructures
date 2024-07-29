//
// Created by mark on 6/2/2021.
//

#include "DSString.h"

DSString::DSString() {
    data = nullptr;
}
DSString::DSString(const char* val){
    if (val == nullptr){
        data = nullptr;
    }
    else {//only runs if val points to something
        data = new char[strlen(val) + 1];
        strcpy(data, val);
        data[strlen(val)] = '\0';
    }
}
DSString::DSString(const DSString& value){
    if (value.data == nullptr){
        data = nullptr;
    }else {//only runs if value.data points to something
        data = new char[strlen(value.data) + 1];
        strcpy(data, value.data);
        data[strlen(value.data)] = '\0';
    }
}
DSString::~DSString(){
    if (data != nullptr) {
        delete[] data;
    }
}
DSString& DSString::operator= (const char* val){
    if (val == nullptr){
        data = nullptr;
    }
    else {//only runs if val points to something
        data = new char[strlen(val) + 1];
        strcpy(data, val);
        data[strlen(val)] = '\0';
    }
    return *this;
}
DSString& DSString::operator= (const DSString& value){
    if (value.data == nullptr){
        data = value.data;
    }//only runs if value.data points to something
    data = new char[strlen(value.data) + 1];
    strcpy(data, value.data);
    data[strlen(value.data)] = '\0';
    return *this;
}
DSString DSString::operator+ (const DSString& value){
    int length = strlen(data) + strlen(value.data) + 1;
    char* str = new char[length];
    str = data;//sets the first part to str
    int x=0;
    for (int i=strlen(data); i<length; i++){//loops through the second char* to pushback the chars to str
        str[i] = value.data[x];
        x++;
    }
    str[length] = '\0';
    DSString final(str);
    return final;
}
bool DSString::operator== (const char* val) const{
    int i = strcmp(data, val);
    if (i == 0) {
        return true;
    } else{//all values other than 0 mean that the two strings are not equal
        return false;
    }
}
bool DSString::operator== (const DSString& value)const{
    int i = strcmp(data, value.data);
    if (i == 0){
        return true;
    } else{//all values other than 0 mean that the two strings are not equal
        return false;
    }
}
bool DSString::operator> (const DSString& value) const{
    int i = strcmp(data, value.data);
    if (i > 0 ){//checks to see which char* is "greater"
        return true;
    } else{
        return false;
    }
}
bool DSString::operator> (const char* val) const{
    int i = strcmp(data, val);
    if (i > 0){//checks to see which char* is "greater"
        return true;
    } else{
        return false;
    }
}
char& DSString::operator[] (const int loc){
    char* str = new char[strlen(data) + 1];//create new char*
    strcpy(str, data);
    str[strlen(data)] = '\0';
    return str[loc];//return specified location of char*
}
int DSString::getLength() const{
    return strlen(data);
}
DSString DSString::substring(int start, int numChars){
    char *sub = new char[numChars + 1];
    int w=0;
    for (int i = start; i < (start+numChars); i++){
        sub[w] = data[i];//adds values to sub for specified area in data
        w++;
    }
    sub[numChars] = '\0';
    DSString substring(sub);
    return substring;
}
char* DSString::c_str(){
    char* dat = new char[strlen(data)+1];
    strcpy(dat,data);
    dat[strlen(data)] = '\0';
    return dat;
}
int DSString::numberOfWords(){
    //code inspired by https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
    int x = 0;
    char* temp = new char[strlen(data) + 1];
    strcpy(temp, data);
    char* words = strtok(temp, " ");//breaks apart string and gets separate words
    while (words != NULL){
        x++;//adds to count for every word found
        words = strtok(NULL, " ");
    }
    return x;
}
DSString DSString::parse(int x){
    //code inspired by https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
    int z = 0;
    char* temp = new char[strlen(data) + 1];
    strcpy(temp, data);
    char* words = strtok(temp, " ");//breaks apart string and gets separate words
    while (words != NULL){
        DSString txt(words);
        if (z == x){
            char* noPunct = new char[500];
            int i=0;
            int w=0;
            while (i<txt.getLength()) {
                if (!ispunct(txt[i])) {//counts ONLY values that are not punctuation
                    noPunct[w] = txt[i]; //then adds those values to a word, ignoring punctuation
                    w++;
                }
                i++;
            }
            DSString dataNew(noPunct);
            return dataNew;
        }
        z++;
        words = strtok(NULL, " ");
    }
}
ostream& operator<< (ostream& file , const DSString& value){
    file << value.data;
    return file;
}
