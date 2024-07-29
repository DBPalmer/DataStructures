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
    //simple destructor for one variable
    if (data != nullptr) {
        delete[] data;
    }
}
DSString& DSString::operator= (const char* val) {
    //first deletes data, then assigns it to val
    delete[] data;
    data = new char[strlen(val)+1];
    strcpy(data, val);
    data[strlen(val)] = '\0';
    return *this;
}
DSString& DSString::operator= (const DSString& value) {
    //first deletes data, then assigns it to value's data
    delete[] data;
    data = new char[strlen(value.data) + 1];
    strcpy(data, value.data);
    data[strlen(value.data)] = '\0';
    return *this;
}
DSString DSString::operator+ (const DSString& value){
    int length = strlen(data) + strlen(value.data);//creates length for finished dsstring
    char str[length+1];
    strcpy(str, data);//sets the first part to str, waiting to add the second part
    int x=0;
    //i starts at the ned of the first since it is adding to, not replacing
    for (int i=strlen(data); i<(length); i++){//loops through the second char* to pushback the chars to str
        str[i] = value.data[x];
        x++;
    }
    str[length] = '\0';
    DSString final(str);
    return final;
}
bool DSString::operator== (const char* val) const{
    //only returns 0 if they are equal
    return strcmp(data, val) == 0;
}
bool DSString::operator== (const DSString& value)const{
    //only returns 0 if they are equal
    return strcmp(data, value.data) == 0;
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
bool DSString::operator< (const DSString& value) const{
    int i = strcmp(data, value.data);
    if (i > 0 ){//checks to see which char* is "less"
        return false;
    } else{
        return true;
    }
}
bool DSString::operator< (const char* val) const{
    int i = strcmp(data, val);
    if (i > 0){//checks to see which char* is "less"
        return false;
    } else{
        return true;
    }
}
char& DSString::operator[] (const int loc){
    if (loc < strlen(data)) {//only runs if loc is in bounds of data
        /*char* str = new char[strlen(data) + 1];//create new char*
        strcpy(str, data);
        str[strlen(data)] = '\0';
        return str[loc];//return specified location of char*
        */
        return data[loc];
    }
}
int DSString::getLength() const{
    //using strlen
    return strlen(data);
}
DSString DSString::substring(int start, int numChars){
    char *sub = new char[numChars + 1];
    int w=0;
    //starts at start value passed, and goes for the int number of chars passed
    for (int i = start; i < (start+numChars); i++){
        sub[w] = data[i];//adds values to sub for specified area in data
        w++;//need the extra w since w and i will increment at different rates
    }
    sub[numChars] = '\0';
    DSString substring(sub);
    delete[] sub;
    return substring;
}
char* DSString::c_str(){
    return data;
}
int DSString::numberOfWords(){
    //code inspired by https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
    int x = 0;
    char* temp = new char[strlen(data) + 1];
    strcpy(temp, data);//temp store data as a copy
    char* words = strtok(temp, " ");//breaks apart string and gets separate words
    while (words != NULL){//while there is a next word in dsstring
        x++;//adds to count for every word found
        words = strtok(NULL, " ");//gets next
    }
    delete[] temp;
    return x;
}
DSString DSString::parse(int x){
    //code inspired by https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
    int z = 0;
    char* temp = new char[strlen(data) + 1];
    strcpy(temp, data);//temp store data as a copy
    char* words = strtok(temp, " ");//breaks apart string and gets separate words
    while (words != NULL){//while there is a next word in dsstring
        DSString txt(words);
        if (z == x){
            char* noPunct = new char[500];
            int i=0;
            int w=0;
            while (i<txt.getLength()) {
                if (!ispunct(txt[i])) {//counts ONLY values that are not punctuation
                    noPunct[w] = txt[i]; //then adds those values to a word, ignoring punctuation
                    w++;//w and i increment at different rates
                }
                i++;
            }
            noPunct[w] = '\0';
            DSString dataNew(noPunct);
            delete[] noPunct;
            delete[] temp;
            return dataNew;
        }
        z++;
        words = strtok(NULL, " ");//gets next
    }
}
ostream& operator<< (ostream& file , const DSString& value){
    file << value.data;
    return file;
}

//ADDED FOR PROJECT 2
DSString DSString::pars(int x, DSString okay){
    //code inspired by https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
    int z = 0;
    char* temp = new char[strlen(data) + 1];
    strcpy(temp, data);//temp store data as a copy
    char* words = strtok(temp, " ");//breaks apart string and gets separate words
    while (words != NULL){//while there is a next word in dsstring
        DSString txt(words);
        if (z == x){
            char* noPunct = new char[100];
            int i=0;
            int w=0;
            while (i<txt.getLength()) {
                if (!ispunct(txt[i])) {//counts ONLY values that are not punctuation
                    noPunct[w] = txt[i]; //then adds those values to a word, ignoring punctuation
                    w++;//w and i increment at different rates
                }
                else {//now even if it is not punct, it might still work if it is one of the puncts used by the terms
                    int cnt = 0;
                    for (int sze=0; sze<okay.getLength(); sze++){//loops through okay puncts found from terms.txt
                        if (txt[i] == okay[sze]){
                            ++cnt;//if it is found
                        }
                    }
                    if (cnt > 0){//also adds that punct to noPunct
                        noPunct[w] = txt[i]; //then adds those values to a word, ignoring punctuation
                        w++;//w and i increment at different rates
                    }
                }
                i++;
            }
            noPunct[w] = '\0';
            DSString dataNew(noPunct);
            delete[] noPunct;
            delete[] temp;
            return dataNew;
        }
        z++;
        words = strtok(NULL, " ");//gets next
    }
}
//ADDED FOR PROJECT 2
DSString DSString::getPunct(){
    char Punct[500];
    int i=0;
    int w=0;
    while (i<strlen(data)) {
        if (ispunct(data[i])) {//counts ONLY values that are punctuation
            if (data[i] != ' ') {//doesnt count spaces
                Punct[w] = data[i];//adds those terms to Punct
                w++;//w and i increment at different rates
            }
        }
        i++;
    }
    Punct[w] = '\0';
    DSString punct(Punct);
    return punct;
}
//ADDED FOR PROJECT 2
void DSString::all_Lower(){
    char* temp = new char[strlen(data) + 1];
    strcpy(temp, data);//temp store data as a copy
    for (int i=0; i<strlen(temp); i++){//loops through data
        data[i] = tolower(temp[i]);//changes all values to lower case
    }
    delete[] temp;
}
