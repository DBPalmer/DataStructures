//
// Created by Deuce Palmer on 4/14/22.
//
//last edit on: 5/02/22
#ifndef INC_22S_FINAL_PROJ_CODERUNNER_H
#define INC_22S_FINAL_PROJ_CODERUNNER_H
#include "include/rapidjson/document.h"
#include "AVLTree.h"
#include "Word.h"
#include "porter2_stemmer.h"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
namespace fs = std::filesystem;

class CodeRunner {
public:
    /**
     * reads stop words file and returns all the words in a unordered map
     */
    unordered_map<string, int>&  getStopWords(string);
    /**
     * reads all the files in the database
     */
    void parseFiles(AVLTree&, AVLTree&, AVLTree&, unordered_map<string, int>&, string, int&, int&);
    /**
     * searches for a string in the files
     */
    vector<Document> findFiles(string, AVLTree&, AVLTree&, AVLTree&);
    /**
     * clears all the AVLTrees if requested by user
     */
    void clearTrees(AVLTree&, AVLTree&, AVLTree&);
     /**
      * saves the contents of the AVLTrees to a files
      */
     void createPresistentIndex(AVLTree&, AVLTree&, AVLTree&);
     /**
      * clears the AVLTrees and then repopulates them with data in persistent index
      */
     void readPresistentIndex(AVLTree&, AVLTree&, AVLTree&);
     /**
      * clears the persistent index
      */
     void clearPresistentIndex();
     /**
      * takes the vector of documents requested from user and prints out the document info
      */
     void queryResults(vector<Document>&, string);
     /**
      * called in main
      */
     void go();
};


#endif //INC_22S_FINAL_PROJ_CODERUNNER_H
