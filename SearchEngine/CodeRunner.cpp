//
// Created by Deuce Palmer on 4/14/22.
//
//last edit on: 5/02/22
#include "CodeRunner.h"
unordered_map<string, int>&  CodeRunner::getStopWords(string file) {
    unordered_map<string, int>* stopWrds = new unordered_map<string, int>;//creates new unordered map
    ifstream stops(file);//opens file
    if (!stops.is_open()) {//checks if file can open
        cout << "Stop Words File failed to open." << endl;
    }
    string word;
    int z = 0;
    while (getline(stops, word)) {
        stopWrds->insert({word, z});//inserts each line (word) into the map
        z++;
    }
    stops.close();
    return *stopWrds;//returns unordered map
}
void CodeRunner::parseFiles(AVLTree& words, AVLTree& pers, AVLTree& orgs, unordered_map<string, int>& stopWrds, string data, int& numberOfJsonsParsed, int& num){
    int x = 0;
    if (num == 0){//since "0" from the user means they want the whole dataset
        num = 400000;//won't limit size
    }
    //file system for loop taken from example repo on website https://github.com/AlexShock66/Reading_In_Directories_Example
    for (const auto &entry: fs::recursive_directory_iterator(data)) {
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".json") {//only parsed if file is a json
                if (numberOfJsonsParsed < num) {
                    numberOfJsonsParsed++;
                    int z = 0;
                    unordered_map<string, int> wordsInFile;//stores Words in map, so the AVL insert doesn't have to be ran as many times
                    //same rapidjson methodology used from repo tutorial in handout https://github.com/Gouldilocks/rapidTutorial/blob/main/main.cpp
                    string filename = entry.path().c_str();
                    rapidjson::Document doc;//create rapidjson document
                    ifstream file(filename);
                    string whole;
                    string temp;
                    while (getline(file, temp)) {//reads all the lines of the file into a string
                        whole += temp;
                    }
                    doc.Parse(whole.c_str());//pass string to doc to be parsed
                    //3 factors used to created relevancy score
                    int rank = doc["thread"]["domain_rank"].GetInt();
                    double spam = doc["thread"]["spam_score"].GetDouble();
                    string pub = doc["thread"]["published"].GetString();
                    Document id(filename, rank, spam, pub);//create document which also calculates relevancy score
                    string s = doc["text"].GetString();//save document text to be parsed
                    //isstringstream iterating method found at https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
                    istringstream text(s);
                    do {
                        string subs;
                        text >> subs;
                        //trim and stem word in document text
                        Porter2Stemmer::trim(subs);
                        Porter2Stemmer::stem(subs);
                        //found iterator functionality from https://www.cplusplus.com/reference/unordered_map/unordered_map/find/
                        unordered_map<string, int>::const_iterator itr1 = wordsInFile.find(subs);
                        if (itr1 == wordsInFile.end()) {//if word has not already been seen in this file
                            wordsInFile.insert({subs, z++});
                            unordered_map<string, int>::const_iterator itr = stopWrds.find(subs);
                            if (itr == stopWrds.end()) {//if the word was not found
                                if (subs != "") {//error catch, can sometimes happen with trimming single punctuation
                                    Word wrd(subs);
                                    words.insert(wrd, id);//add it to the AVLTree, with duplicate handling
                                }
                            }
                        }
                    } while (text);
                    unordered_map<string, int> persInFile;
                    int q=0;
                    //for loop functionality used from rapidjson handout repo https://github.com/Gouldilocks/rapidTutorial/blob/main/main.cpp
                    for (auto &v: doc["entities"]["persons"].GetArray()) {
                        string name = v["name"].GetString();//only worried about the name of the person
                        //trim and stem the name to stay consistent
                        Porter2Stemmer::trim(name);
                        Porter2Stemmer::stem(name);
                        unordered_map<string, int>::const_iterator itr = persInFile.find(name);
                        if (itr == persInFile.end()) {//if the person has not already been seen in this file
                            persInFile.insert({name, q++});
                            Word nme(name);
                            pers.insert(nme, id);//insert the person and its id into the pers AVLTree
                        }
                    }
                    unordered_map<string, int> orgsInFile;
                    int r=0;
                    //for loop functionality used from rapidjson handout repo https://github.com/Gouldilocks/rapidTutorial/blob/main/main.cpp
                    for (auto &v: doc["entities"]["organizations"].GetArray()) {
                        string orgg = v["name"].GetString();//only worried about the name of the org
                        //trim and stem the name to stay consistent
                        //NOTE: will make multiple word orgs all one word
                        Porter2Stemmer::trim(orgg);
                        Porter2Stemmer::stem(orgg);
                        unordered_map<string, int>::const_iterator itr = orgsInFile.find(orgg);
                        if (itr == orgsInFile.end()) {//if the org has not already been seen in this file
                            orgsInFile.insert({orgg, r++});
                            Word org(orgg);
                            orgs.insert(org, id);//insert the org and its id into the orgs AVLTree
                        }
                    }
                }
            }
        }
    }
}
vector<Document> CodeRunner::findFiles(string sent, AVLTree& wrds, AVLTree& pers, AVLTree& orgs){
    //need to trim and stem the words, just like all the entries in the AVLTree
    //isstringstream iterating method found at https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
    //std::chrono used from PA03
    chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = chrono::high_resolution_clock::now();//timer starts
    vector<Document> docs;
    istringstream query(sent);//parsing the query sentence from user
    string s,one,two;
    query >> s;//gets first word
    do {
        if (s == "OR") {
            query >> one;
            //trim and stem word
            Porter2Stemmer::trim(one);
            Porter2Stemmer::stem(one);
            Word ss(one);//created a Word object
            if (wrds.contains(ss)) {//checks if the Word is in the AVLTree
                docs = wrds.find(ss).getDoc();//gets all of its documents and adds it to docs
            } else {
                cout << "Query is still running, but note that the word '" << one << "' was not found in the database"
                     << endl;
            }
            query >> s;//get next word in query
            //trim and stem word
            Porter2Stemmer::trim(s);
            Porter2Stemmer::stem(s);
            while (s != "NOT" && s != "ORG" && s != "PERSON" && s != "") {//since there can be 2 or more OR words
                //trim and stem word
                Porter2Stemmer::trim(s);
                Porter2Stemmer::stem(s);
                Word aa(s);//created a Word object
                if (wrds.contains(aa)) {//checks if the Word is in the AVLTree
                    vector<Document> ids = wrds.find(aa).getDoc();//save documents
                    for (int i = 0; i < ids.size(); i++) {//for all ids found in aa word
                        if (std::find(docs.begin(), docs.end(), ids[i]) == docs.end()) {//in order to not add the same document twice
                            docs.push_back(ids[i]);
                        }
                    }
                } else {
                    cout << "Query is still running, but note that the word '" << s
                         << "' was not found in the database" << endl;
                }
                string q;//getting the next word in query, for some reason just "query >> s" wouldnt work
                query >> q;
                s = q;
            }
        }
        else if (s == "AND") {
            query >> one;
            //trim and stem word
            Porter2Stemmer::trim(one);
            Porter2Stemmer::stem(one);
            Word ss(one);//created a Word object
            if (wrds.contains(ss)) {//checks if the Word is in the AVLTree
                docs = wrds.find(ss).getDoc();//ids begins with those contained in the first word, ids will not grow past this since AND stmt
            }
            else {
                cout << "AND statement fails to return any documents since the word '" << one << "' was not found in the database\n";
            }
            query >> s;//get next word in query
            //trim and stem word
            Porter2Stemmer::trim(s);
            Porter2Stemmer::stem(s);
            while (s != "NOT" && s != "ORG" && s != "PERSON" && s != "") {//since there can be 2+ words in AND stmts
                //trim and stem word
                Porter2Stemmer::trim(s);
                Porter2Stemmer::stem(s);
                Word aa(s);//created a Word object
                vector<Document> temp = docs;//temporarily stores docs in temp, easy way to remove documents not found in any words
                docs.clear();
                if (!wrds.contains(aa)) {//checks if the Word is in the AVLTree
                    cout << "AND statement fails to return any documents since the word '" << s
                         << "' was not found in the database\n";
                    temp.clear();//by def of AND stmt, there will be no documents if one word is not found
                } else {
                    Word find = wrds.find(aa);
                    for (int i = 0; i < temp.size(); i++) {//for ids in first word
                        if (find.search(temp[i])) {//if term is not found in aa word, it needs to be removed
                            docs.push_back(temp[i]);//adding temp value back to docs
                        }
                    }
                }
                string q;//getting the next word in query, for some reason just "query >> s" wouldnt work
                query >> q;
                s = q;
            }
        }
        else if (s == "NOT") {
            query >> one;
            //trim and stem word
            Porter2Stemmer::trim(one);
            Porter2Stemmer::stem(one);
            Word ss(one);//created a Word object
            if (wrds.contains(ss)) {//checks if the Word is in the AVLTree
                Word find = wrds.find(ss);
                vector<Document> temp = docs;//stores current docs in temp
                docs.clear();//clears docs
                for (int i = 0; i < temp.size(); i++) {//for all elements that used to be in docs
                    if (!find.search(temp[i])){//if the NOT word is not found
                        docs.push_back(temp[i]);//add it back to docs
                    }
                }
            }
            else {
                cout << "Query is still running, but note that the word '"<< one <<"' was not found in the database, so no documents have been removed" << endl;
            }
            query >> s;
        }
        else if (s == "PERSON") {
            query >> one;
            //trim and stem person
            Porter2Stemmer::trim(one);
            Porter2Stemmer::stem(one);
            Word ss(one);//created a Word object
            vector<Document> temp = docs;//stores current docs in temp
            docs.clear();//clears docs
            if (pers.contains(ss)) {//checks if the Word is in the AVLTree
                Word find = pers.find(ss);
                for (int i = 0; i < temp.size(); i++) {//for documents that used to be in docs
                    if (find.search(temp[i])){//if person is found
                        docs.push_back(temp[i]);//add it back to docs
                    }
                }
            }
            else {
                cout << "The Person '"<< one <<"' was not found in the database. Therefore there are no available files meeting the criteria you have requested.\n";
            }
            query >> s;
        }
        else if (s == "ORG") {
            query >> one;
            //trim and stem org
            Porter2Stemmer::trim(one);
            Porter2Stemmer::stem(one);
            Word ss(one);//created a Word object
            vector<Document> temp = docs;//stores current docs in temp
            docs.clear();//clears docs
            if (orgs.contains(ss)) {//checks if the Word is in the AVLTree
                Word find = orgs.find(ss);
                for (int i = 0; i < temp.size(); i++) {//for documents that used to be in docs
                    if (find.search(temp[i])){//if org is found
                        docs.push_back(temp[i]);//add it back to docs
                    }
                }
            }
            else {
                cout << "The Organization '"<< one <<"' was not found in the database. Therefore there are no available files meeting the criteria you have requested.\n";
            }
            query >> s;
        }
        else if (s == ""){query >> s;}//do nothing, just a catch
        else {
            //trim and stem word
            Porter2Stemmer::trim(s);
            Porter2Stemmer::stem(s);
            Word ss(s);//created a Word object with s as word
            if (wrds.contains(ss)) {//checks if the Word is in the AVLTree
                docs = wrds.find(ss).getDoc();//add all the document to docs that word was found in
            } else {//if not found
                cout << "The word '"<< s << "' was not found in any documents\n";
            }
            query >> s;
        }
    } while (query);
    //std::chrono used from PA03
    end = chrono::high_resolution_clock::now();//timer ends
    chrono::duration<double> time_in_seconds = end - start;
    if (docs.size() > 0){//print out of query time
        cout << fixed << endl << docs.size() << " Documents found in " << time_in_seconds.count() << " seconds\n" << endl;
    } else {//modified if no documents were found
        cout << fixed << "\nAlthough unsuccessful in finding any documents...Query request completed in " << time_in_seconds.count() << " seconds\n" << endl;
    }
    return docs;
}
void CodeRunner::clearTrees(AVLTree& words, AVLTree& pers, AVLTree& orgs){
    //deletes all the nodes in each tree
    words.makeEmpty();
    pers.makeEmpty();
    orgs.makeEmpty();
}
void CodeRunner::createPresistentIndex(AVLTree& words, AVLTree& pers, AVLTree& orgs){
    ofstream wordFile("Words.txt");//opening file with name passed in
    if (!wordFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    words.printTreeToFile(wordFile);//print words to wordFile
    wordFile.close();
    ofstream persFile("Persons.txt");//opening file with name passed in
    if (!persFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    pers.printTreeToFile(persFile);//print persons to persFile
    persFile.close();
    ofstream orgFile("Organizations.txt");//opening file with name passed in
    if (!orgFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    orgs.printTreeToFile(orgFile);//print orgs to orgFile
    orgFile.close();
}
void CodeRunner::readPresistentIndex(AVLTree& words, AVLTree& pers, AVLTree& orgs){
    clearTrees(words, pers, orgs);//clears data currently indexed in memory, so it can be replaced
    ifstream wordFile("Words.txt");//opening file with name passed in
    if (!wordFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    string name, id, score;
    getline(wordFile, name, ' ');//gets name
    while (!wordFile.eof()) {
        Word wrd(name);
        string num;
        string blank;
        getline(wordFile, num, ' ');//number of docs is next
        int numb = stoi(num);
        for (int i=0; i<numb; i++){//exactly enough to get the number of docs that the word has
            getline(wordFile, id, ',');//gets id
            getline(wordFile, score, ' ');//gets score
            double scre = stod(score);
            Document doc(id, scre);//creates doc
            wrd.push_back(doc);//adds doc to that word
        }
        words.insert(wrd);//word is inserted into AVLTree with all of its documents
        getline(wordFile, blank);//gets newline
        getline(wordFile, name, ' ');//process restarts
    }
    wordFile.close();

    ifstream persFile("Persons.txt");//opening file with name passed in
    if (!persFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    getline(persFile, name, ' ');//gets name
    while (!persFile.eof()) {
        Word wrd(name);
        string num;
        string blank;
        getline(persFile, num, ' ');//number of docs is next
        int numb = stoi(num);
        for (int i=0; i<numb; i++){//exactly enough to get the number of docs that the word has
            getline(persFile, id, ',');//gets id
            getline(persFile, score, ' ');//gets score
            double scre = stod(score);
            Document doc(id, scre);//creates doc
            wrd.push_back(doc);//adds doc to that word
        }
        pers.insert(wrd);//person is inserted into AVLTree with all of its documents
        getline(persFile, blank);//gets newline
        getline(persFile, name, ' ');//process restarts
    }
    persFile.close();

    ifstream orgFile("Organizations.txt");//opening file with name passed in
    if (!orgFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    getline(orgFile, name, ' ');//gets name
    while (!orgFile.eof()) {
        Word wrd(name);
        string num;
        string blank;
        getline(orgFile, num, ' ');//number of docs is next
        int numb = stoi(num);
        for (int i=0; i<numb; i++){//exactly enough to get the number of docs that the word has
            getline(orgFile, id, ',');//gets id
            getline(orgFile, score, ' ');//gets score
            double scre = stod(score);
            Document doc(id, scre);//creates doc
            wrd.push_back(doc);//adds doc to that word
        }
        orgs.insert(wrd);//org is inserted into AVLTree with all of its documents
        getline(orgFile, blank);//gets newline
        getline(orgFile, name, ' ');//process restarts
    }
    orgFile.close();
}
void CodeRunner::clearPresistentIndex(){
    ofstream wordFile("Words.txt");//opening file with name passed in
    if (!wordFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    wordFile.clear();//clear file
    wordFile.close();
    ofstream persFile("Persons.txt");//opening file with name passed in
    if (!persFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    persFile.clear();//clear file
    persFile.close();
    ofstream orgFile("Organizations.txt");//opening file with name passed in
    if (!orgFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    orgFile.clear();//clear file
    orgFile.close();
}
void CodeRunner::queryResults(vector<Document>& docs, string data){
    //implementation of the simple selection sort found via https://www.geeksforgeeks.org/selection-sort/
    //comparing only the scores to sort, the smallest scores are the best
    int i, j, min;
    for (i = 0; i < docs.size()-1; i++) {
        min = i;//sets min
        for (j = i + 1; j < docs.size(); j++) {
            if (docs[j] < docs[min]) {//implementation of the "<" op for Documents compares relevancy score
                min = j;//will change min if smaller score is found
            }
        }
        swap(docs[min], docs[i]);//swaps values
    }
    int x=1;
    vector<string> texts;//stores the full text of each article
    for (const auto &entry: fs::recursive_directory_iterator(data)) {
        if (entry.is_regular_file()) {
            for (int i = 0; i < docs.size(); i++) {
                if (i<15) {//request to max file output to 15 via handout
                    string filename = entry.path().c_str();
                    if (docs[i].getId() == filename) {//if filename is one of the documents in docs
                        rapidjson::Document doc;//create rapidjson document
                        ifstream file(filename);
                        string whole;
                        string temp;
                        while (getline(file, temp)) {//reads all the lines of the file into a string
                            whole += temp;
                        }
                        doc.Parse(whole.c_str());//pass string to doc to be parsed
                        //print out of summary stats on document
                        cout << "#" << x++ << ": ";
                        string url = doc["thread"]["url"].GetString();
                        cout << url << endl;
                        string source = doc["thread"]["site"].GetString();
                        cout << "\tSource: " << source << endl;
                        string title = doc["thread"]["title"].GetString();
                        cout << "\tTitle: " << title << endl;
                        string pub = doc["thread"]["published"].GetString();
                        string pubb = pub.substr(0,10);//only captures year-month-day
                        cout << "\tDate published: " << pubb << endl;
                        string text = doc["text"].GetString();
                        texts.push_back(text);//saves all the texts of the 15 documents so that they can be printed out if requested
                    }
                }
            }
        }
    }
    string choice;
    while (choice != "-1") {
        cout << "\nTo view the full text, type the corresponding article number\nEnter -1 to return to main menu.\n";
        cin >> choice;
        if (choice != "-1") {
            if (choice == "1" || choice == "2" ||choice == "3" ||choice == "4" ||choice == "5" ||choice == "6" ||choice == "7" ||choice == "8" ||choice == "9" ||choice == "10" ||choice == "11" ||choice == "12" ||choice == "13" ||choice == "14" ||choice == "15") {
                int num = stoi(choice);//change it to an int
                if (num > texts.size()) {//user error check
                    cout << "Error: out of range. Please enter a number that corresponds to an article above.\n";
                } else {
                    for (int i = 0; i < texts.size(); i++) {//when choice is found
                        if (num - 1 == i) {
                            cout << "\nFull text of Document #" << num << ":" << endl;
                            cout << "\t" << texts[i] << endl;//print out the full text of doc requested
                        }
                    }
                }
            }
            else {
                cout <<"Please enter a valid article number.\n";
            }
        } else {
            cout << "\nReturning to main menu...\n";
        }
    }
}
void CodeRunner::go(){
    unordered_map<string, int> stopWords = getStopWords("stopwords.txt");//stores stop words
    //AVLTrees
    AVLTree words;
    AVLTree persons;
    AVLTree organizations;
    int numberOfJsonsParsed = 0;//summary stat
    string dataset;
    string choice;
    cout << "Enter dataset to be parsed: (enter 'skip' to bypass this step)\n";
    cin >> dataset;//gets dataset from user
    //dataset = "/Users/deucepalmer/Downloads/archive";
    if (dataset != "skip") {//skip will be used to run the program again and just access the persistent index
        string size;
        cout << "If you want to parse a certain number of jsons, type that number below, or enter 0 to parse the entire dataset\n";//gives the user the option to use a sample
        cin >> size;
        int sze = stoi(size);//turns string into int
        parseFiles(words, persons, organizations, stopWords, dataset, numberOfJsonsParsed, sze);//parses documents in the dataset
        cout << "Parsing complete\n";
    }
    int x = 0;
    while (x == 0) {//main menu loop
        cout << "============================================\n";
        cout << "Please select from menu:\n  1. Enter query\n  2. Manage Index\n  3. Print Statistics\n  4. Clear Index\nEnter -1 to exit\n";
        cout << "============================================\n";
        cout << "Please enter your selection by typing the corresponding number\n";
        cin >> choice;
        if (choice == "1") {
            cout << "Enter query:\n";
            string first, rest, query;
            //strange method I figured out to get all the words in a sentence in cin
            cin >> first;
            getline(cin, rest);
            query = first + rest;
            vector<Document> results = findFiles(query, words, persons, organizations);//returns the files that are obtained by query
            if (results.size() > 0) {//otherwise SIGSEGV error
                queryResults(results, dataset);//prints out the documents and their data
            }
        }
        else if (choice == "2"){
            cout << "\nHow would you like to manage the index?\n";
            int z=0;
            while (z == 0) {
                cout << "1. Create persistent index\n2. Read from persistent index\n3. Clear persistent index\nEnter -1 to exit\n";
                cin >> choice;
                if (choice == "1") {
                    createPresistentIndex(words, persons, organizations);//creates persistent index
                }
                else if (choice == "2") {
                    readPresistentIndex(words, persons, organizations);//reads persistent index
                }
                else if (choice == "3") {
                    clearPresistentIndex();//clears persistent index
                }
                else if (choice == "-1") {
                    z++;//brakes loop
                    cout << "\nReturning to main menu...\n";
                } else {
                    cout << "Please enter a valid menu option.\n";
                }
            }
        }
        else if (choice == "3"){
            cout << "Total jsons initially parsed: " << numberOfJsonsParsed << endl;
            cout << "Total number of unique words: " << words.count() << endl;//size of pairs is the same as count
            cout << "                     persons: " << persons.count() << endl;//person count
            cout << "               organizations: " << organizations.count() << endl;// org count
            int x=1;
            cout << "To view the top 25 most frequent words, enter 1. Type anything else to bypass\n";
            string topWords;
            cin >> topWords;
            if (topWords == "1") {
                vector<pair<int, string>> pairs = words.topWords();//gets pairs for top 25 words
                if (pairs.size() > 0) {//otherwise SIGSEGV
                    cout << "Top 25 most common words in the database:\n";
                    std::sort(pairs.begin(), pairs.end());//sorts based on the int, not the string
                    for (int i = pairs.size() - 1;
                         i > pairs.size() - 26; i--) {//the last 25 terms (words with the most appearances)
                        cout << "\t#" << x++ << ": " << pairs[i].second << endl;//second is the word itself
                    }
                }
            }
            cout << endl;
        }
        else if (choice == "4"){
            clearTrees(words, persons, organizations);
            cout << "The index has been cleared.\n\n";
        }
        else if (choice == "-1") {
            cout << "Exited Successfully. Thank You.\n";
            x++;//ends loop
        }
        else {
            cout << "Invalid menu option. Please try again.\n";
        }
    }
}