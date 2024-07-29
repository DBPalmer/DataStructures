//
// Created by Deuce Palmer on 3/3/22.
//

#ifndef INC_21F_PA02_CODERUNNER_H
#define INC_21F_PA02_CODERUNNER_H
#include <iostream>
#include <fstream>
#include "DSString.h"
#include "DSVector.h"

class CodeRunner {
public:
    /**
     * constructor
     */
    CodeRunner();
    /**
     * will read the two file names passed in while editing the two dsvectors
     */
    void readFiles(DSString, DSString, DSVector<DSString>&, DSVector<DSVector<int>>&);
    /**
     * final ouput to file passed in as dsstring, maintains necessary data from both dsvectors needed for output
     */
    void output(DSString, DSVector<DSString>&, DSVector<DSVector<int>>&);
};

#endif //INC_21F_PA02_CODERUNNER_H
