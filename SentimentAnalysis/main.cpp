#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "DSString.h"
#include "Tweet.h"
#include "catch.hpp"
using namespace std;
int run(char**);
int test();
int main(int argc, char** argv) {
    if (argc == 1)
        return test();
    return run(argv);
}
int test(){
    return Catch::Session().run();
}
int run(char** argv){
    vector <Tweet> twitter;//stores tweets from training dataset
    vector <Tweet> twitter2;//stores tweets from testing dataset
    unordered_map<DSString, double> dictionary;//stores all the words from testing, map used to find words quickly
    ifstream testFile;
    testFile.open(argv[1]);
    if (!testFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    char skip[5000], title[5000], tweet[5000], id[5000], sent[5000];
    testFile.getline(title, 5000);
    while (!testFile.eof()){
        testFile.getline(sent, 5000, ',');
        DSString sentiment(sent);
        testFile.getline(id, 5000, ',');
        DSString ident(id);
        testFile.getline(skip, 5000, ',');//skips all the other data in the file
        testFile.getline(skip, 5000, ',');
        testFile.getline(skip, 5000, ',');
        testFile.getline(tweet, 5000);
        DSString sentence(tweet);
        Tweet entry(ident, sentiment, sentence);//saves line in file to a tweet object
        entry.parse(dictionary); //saves all the words in dictionary vector, creating or adjusting their sentiment
        twitter.push_back(entry);
    }
    twitter.pop_back();//since file ends with new line, this will delete the last one created
    testFile.close();
    ifstream inFile;
    inFile.open(argv[2]);
    if (!inFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    inFile.getline(title, 5000);
    while (!inFile.eof()){
        inFile.getline(id, 5000, ',');
        DSString ident(id);
        inFile.getline(skip, 5000, ',');//skips all the other data in the file
        inFile.getline(skip, 5000, ',');
        inFile.getline(skip, 5000, ',');
        inFile.getline(tweet, 5000);
        DSString sentence(tweet);
        Tweet entry(ident, sentence); //saves line again, but without sentiment
        entry.calcSent(dictionary);//will parse but then compare it to the values in dictionary in order to set the tweet sentiment
        twitter2.push_back(entry);
    }
    twitter2.pop_back();//since file ends with new line, this will delete the last one created
    inFile.close();
    ifstream checkFile;
    checkFile.open(argv[3]);
    if (!checkFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    checkFile.getline(title, 5000);
    int right = 0;
    vector <DSString> wrongs;//used for file output of incorrect calculations
    int s = -1;
    while (!checkFile.eof()){
        checkFile.getline(sent, 5000, ',');
        s++;
        DSString sentiment(sent);
        checkFile.getline(id, 5000);
        DSString ident(id);
        for (int z = 0; z < twitter2.size(); z++) {
            if (ident == twitter2[z].getId()) {// finding the same tweet by ID
                if (sentiment == twitter2[z].getSent()) {
                    right++;
                } else { //if sentiment calculation was wrong, it will add to vector to be printed in output file
                    wrongs.push_back(ident);
                }
            }
        }
    }
    checkFile.close();
    ofstream outfile;
    outfile.open(argv[4]);
    float percentage = right/double(s);
    outfile << setprecision(3) << percentage << endl;//sets to three decimals
    for (int q=0; q<wrongs.size();q++){
        outfile << wrongs[q] << endl;
    }
    outfile.close();
    return 0;
}

