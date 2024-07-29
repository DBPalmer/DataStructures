//
// Created by Deuce Palmer on 2/16/22.
//
#ifndef INC_21F_PA02_DSVECTOR_H
#define INC_21F_PA02_DSVECTOR_H
#include "DSString.h"
#include <fstream>
template <typename T>

class DSVector {
private:
    DSString name;
    T* data;
    int size = 0;
    int capacity = 0;
    int it = 0;//iterator
public:
    /**
     * constructors and destructor
     */
    DSVector();
    DSVector(DSString&);
    DSVector(const DSVector<T>&);
    ~DSVector();
    /**
     * overloaded asg operator
     */
    DSVector<T>& operator=(const DSVector<T>&);
    /**
     * subscript operator to return index of DSVector
     * no bound checking
     * @return value at index by reference
     */
    T& operator[](const int&);
    /**
     * at operator to return index of DSVector
     * with bound checking
     * @return value at index by reference
     */
    T& at(const int&);
    /**
     * adds a value to the end of the vector
     * @return value that was pushed back
     */
    T& push_back(T&);
    /**
     * removes and returns the last value of the vector
     * @return popped back value
     */
    T& pop_back();
    /**
     * @return size of vector as an integer
     */
    int getSize()const;
    /**
     * @return the name of the vector as dsstring
     */
    DSString getName()const;
    /**
     * @return capcity of vector as an integer
     */
    int getCapacity()const;
    /**
     * double the vector's capacity
     */
    void resize();
    /**
     * removes element at index passed, decreases size by 1 as well
     */
    void remove(int);
    /**
     * searches for the data value past
     * @return location of element. If it is not found, -1 will be returned
     */
     int search(T&);
    /**
    * searches for the data value past, while keeping punctuation passed in by dsstring while parsing
    * @return location of element. If it is not found, -1 will be returned
    */
    int search(T, DSString);
     /**
      * sorts vector elements alphabetically if DSString OR numerically if ints
      */
      void sort();
      /**
       * sets iterator to start of DSVector
       */
      void reset_iterator();
      /**
       * Checks to see if the iterator has reached the end of the DSVector
       * @return true if there is more elements, false if iterator is at the end
       */
      bool has_next();
      /**
       * gets the next element in DSVector
       * @return element of T type at next index
       */
      T& get_next();
      /**
       * used to search dsvector for the names of the double vector, ingoring punctuation of T& while parsing phrases
       */
      void compare(DSVector<DSVector<int>>&, T&);
      /**
       * displays final index to argv[3], which is passed in as dsstring. Since char* not allowed
       */
      void display(DSString, DSVector<DSVector<int>>&);
};
template <typename T>
DSVector<T>::DSVector(){
    //automatically creates cap of 10 and dynamically allocated data
    name = "";
    size = 0;
    capacity = 10;
    data = new T[capacity];
}
template <typename T>
DSVector<T>::DSVector(DSString& nme){
    //dsstring of nme is used to store name, will be used as an identifier
    //automatically creates cap of 10 and dynamically allocated data
    name = nme;
    size = 0;
    capacity = 10;
    data = new T[capacity];
}
template <typename T>
DSVector<T>::DSVector(const DSVector<T>& arg){
    //copies all 4 private data types (except it) from arg
    name = arg.name;
    capacity = arg.capacity;
    size = arg.size;
    data = new T[capacity];
    for (int i=0; i<size; i++){//needs to be copied over one by one
        data[i] = arg.data[i];
    }
}
template <typename T>
DSVector<T>::~DSVector(){
    //not needed for ints and dsstring has its own destructor
    if (data != nullptr) {
        delete[] data;
    }
}
template <typename T>
DSVector<T>& DSVector<T>::operator=(const DSVector<T>& arg) {
    //copies all 4 private data types (except it) from arg
    delete[] data;//first, the current data needs to be deleted
    name = arg.name;
    it = 0;
    capacity = arg.capacity;
    size = arg.size;
    data = new T[capacity];
    for (int i = 0; i < size; i++) {//needs to be copied over one by one
        data[i] = arg.data[i];
    }
    return *this;//return the new this copied from args
}
template <typename T>
T& DSVector<T>::operator[](const int& index){
    //no bound checking
    return data[index];
}
template <typename T>
T& DSVector<T>::at(const int& index){
    if (index < size) {//bound checking
        return data[index];
    }
}
template <typename T>
T& DSVector<T>::push_back(T& val){
    if (size == capacity){//since we are changing the dsvectors size, we need to check if it is equal to the cap
        resize();//if it is, cap will double therefore creating more space
    }
    data[size] = val;
    size++;//add to size since value was added
    return val;//returns pushed back value in order to apply functionality to, if needed
}
template <typename T>
T& DSVector<T>::pop_back(){
    T* val = &data[size-1];//gets last element
    size--;//reduces size
    return *val;//returns that last element which was removed
}
template <typename T>
int DSVector<T>::getSize()const{
    return size;
}
template <typename T>
DSString DSVector<T>::getName()const{
    return name;
}
template <typename T>
int DSVector<T>::getCapacity()const{
    return capacity;
}
template <typename T>
void DSVector<T>::resize(){
    T* temp = new T[capacity*2];//new T* with a doubled capacity
    for (int i=0; i<size; i++){//sets the elements that were in data to temp
        temp[i] = data[i];
    }
    delete[] data;//deletes data, no longer needed since its values are stored in temp;
    data = temp;
    capacity*=2;//doubles capacity
}
template <typename T>
void DSVector<T>::remove(int index){
    if (index < size){//bound check for index
        for (int i=index; i<(size-1); i++){//since one element is removed, all the others behind it need to move their index up 1
            data[i] = data[i+1];
        }
        size--;//accounts for the 1 removed element
    }
}
template <typename T>
int DSVector<T>::search(T& val){
    int x=0;
    for (int i=0; i<size; i++){//loops through data
        if (data[i] == val){//looks for val
            x++;
            return i;//returns index at which val was found
        }
    }
    if (x == 0){//only runs if val not found
        return -1;
    }
}
//same as first search but with punct used during parsing a search of phrases
template <typename T>
int DSVector<T>::search(T val, DSString punct) {
    int x=0;
    for (int i=0; i<size; i++){//loops through data
        int add = 0;
        if (data[i] == val.pars(0, punct)) {//gets first parsed word being searched for
            add++;
            for (int s = 1; s < val.numberOfWords(); s++) {//continues for total words in phrase
                DSString prse(val.pars(s, punct));//continues to parse, while ignoring allowed punctuation
                if ((i+s) < size) {//...this was a headache. I was sometimes comparing data values that were out of range
                    if (prse == data[i + s]) {
                        add++;
                    }
                }
            }
            if (add == val.numberOfWords()){//means that each word in phrase was found in data
                x++;//value was found
                return i;//returns index
            }
        }
    }
    if (x == 0){//only runs if val not found
        return -1;
    }
}
template <typename T>
void DSVector<T>::sort() {
    //2 for loops to compare each element to all the others
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (data[i] < data[j]) {//if the first element being compared is < the second, they need to swap
                T temp = data[j];//holds data[j]
                data[j] = data[i];//sets data[j] to data[i]
                data[i] = temp;//sets data[i] to the value held in temp
            }
        }
    }
}
template <typename T>
void DSVector<T>::reset_iterator(){
    it = 0;
}
template <typename T>
bool DSVector<T>::has_next(){
    //takes the next element and compares it to the end of data, same as (it+1) >= (size-1)
    if (it >= (size)){
        return false;//if there is no more elements in dsvector
    }else{
        return true;//if there is more elements in dsvector
    }
}
template <typename T>
T& DSVector<T>::get_next(){
    //returns data at the index of it, then increments it
    return data[it++];
}
template <typename T>
void DSVector<T>::compare(DSVector<DSVector<int>>& trm, T& punct) {
    for (int i = 0; i < trm.getSize(); i++) {
        if (this->search(trm[i].getName(), punct) != -1){
            int num = stoi(this->name.c_str());//need to change to int so that the sort function will work for integers, not DSStrings
            trm[i].push_back(num);
        }
        trm[i].sort();//sorts the integers from least to greatest
    }
}
template <typename T>
void DSVector<T>::display(DSString output, DSVector<DSVector<int>>& trms){
    DSString alphabet("123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");//used to print out correct [header]
    ofstream outFile;
    outFile.open(output.c_str());//opening file with name passed in
    if (!outFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    int w=-1;
    for (int i=0; i<trms.getSize(); i++){//entire loop to remove double occurrences of the same page number
        for (int j=0; j<trms[i].getSize(); j++){
            for (int l=0; l<trms[i].getSize(); l++){
                if (l != j){//only runs if not comparing the same index to itself
                    if (trms[i][j] == trms[i][l]){//if they equal, one will be removed
                        trms[i].remove(l);
                    }
                }
            }
        }
    }
    for (int i=0; i<trms.getSize(); i++){//loops through terms
        for (int j=0; j<alphabet.getLength(); j++){//loops through alphabet
            if (trms[i].getName()[0] == tolower(alphabet[j]) && w!=j){//finds what the starting char is
                outFile << "[" <<alphabet[j] << "]\n";//will print the corresponding letter
                w = j;//w is used so that not every term has its own header, will only change when the first letter changes
            }
        }
        int line = 0;
        line += trms[i].getName().getLength() + 2;// line starts with trm length and 2 more for ": "
        if (line >= 70) {//cautious if just in case massive term is longer than 70 chars
            int len = trms[i].getName().getLength();
            outFile << trms[i].getName().substring(0, 70) << endl;
            outFile << "    " << trms[i].getName().substring(70,len-70) << ": ";
            line = trms[i].getName().substring(70,len-70).getLength() + 6;//subscript on next line plus 6 for ": " and 4spaces
        }else {
            outFile << trms[i].getName() << ": ";
        }
        for (int z=0; z<trms[i].getSize(); z++){
            int wrd = to_string(trms[i][z]).length();
            line += wrd;//gets the size in chars of the entry and adds it to line
            if (z == (trms[i].getSize()-1)){
                if (line <= 70) {//if the handout prescribed end of line is not reached
                    outFile << trms[i][z];//just the last element, so no comma needed
                } else {
                    outFile << endl << "    " << trms[i][z];//newline and 4spaces as requested in handout
                    line = 4 + wrd;//resets line, but accounts for the 4 spaces and term
                }
            } else {
                line += 2;// for the ',' and the space ' '
                if (line <= 70) {//if the handout prescribed end of line is not reached
                    outFile << trms[i][z] << ", ";
                } else {
                    outFile << endl << "    " << trms[i][z] << ", ";//newline and 4spaces as requested in handout
                    line = 4 + wrd + 2;//resets line, but accounts for the 4 spaces and term and ", "
                }
            }
        }
        outFile << endl;
    }
    outFile.close();
}
#endif //INC_21F_PA02_DSVECTOR_H
