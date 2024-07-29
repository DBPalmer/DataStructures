//
// Created by Deuce Palmer on 3/3/22.
//

#include "CodeRunner.h"
CodeRunner::CodeRunner(){
}
void CodeRunner::readFiles(DSString ar1, DSString ar2, DSVector<DSString>& wordSort, DSVector<DSVector<int>>& terms) {
    ifstream termFile;
    termFile.open(ar2.c_str());
    if (!termFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    char term[1000];
    termFile.getline(term, 1000);
    DSString punct("");//stores allowed punctuation
    while (!termFile.eof()){
        DSString word(term);
        punct = punct + word.getPunct();//used to add allowed punctuation to punct
        word.all_Lower();//makes comparing much easier
        wordSort.push_back(word);//collecting terms in a dsstring vector
        termFile.getline(term, 1000);
    }
    wordSort.sort();//sorting terms here, since not able to once in terms
    for (int i=0; i<wordSort.getSize(); i++){//now adding those terms to the double vector as names, since sort doesnt sort based on names
        DSVector<int> trm(wordSort[i]);
        terms.push_back(trm);
    }
    termFile.close();
    ifstream bookFile;
    bookFile.open(ar1.c_str());
    if (!bookFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    char c[5000];
    bookFile.getline(c, 5000);
    while(true){//works for one time, but not for anything more than that
        if (c[0] == '<' && c[1] == '-'){//loops runs until <-1> is reached
            break;
        }
        if (c[0] == '<') {//means next page has been reached
            int i = 1;
            char numb[1000];//temporarily storing while being read from file
            int w = 0;
            while (c[i] != '>') {
                numb[w] = c[i];//grabs page numbers
                i++;
                w++;//w and i are not equal, therefore need separate index variables i & w
            }
            numb[w] = '\0';
            DSString pgnmb(numb);
            DSVector<DSString> page(pgnmb);//creating vector with page number as name
            bookFile.getline(c, 5000);
            DSString pge(c);
            pge = pge + " ";//gets the first line of text, plus a space needed later to parse
            bookFile.getline(c, 5000);
            while (c[0] != '<') {//until the next page is reached
                pge = pge + c + " ";// keep adding the lines of text to dsstring pge
                bookFile.getline(c, 5000);
            }
            for (int q = 0; q < pge.numberOfWords(); q++) {// for the number of words on the page
                DSString entry(pge.pars(q, punct));//parse each word into its own dsstring and take out punctuation, BUT keep what is allowed by punct
                entry.all_Lower();//makes comparing much easier
                page.push_back(entry);//adds each word to the page vector
            }
            page.compare(terms, punct);//searches for term words, that are also on the page, while ignoring punctuation is punct
        }
    }
    bookFile.close();
}
void CodeRunner::output(DSString output, DSVector<DSString>& wordSort, DSVector<DSVector<int>>& terms){
    wordSort.display(output, terms);//final display of index
}