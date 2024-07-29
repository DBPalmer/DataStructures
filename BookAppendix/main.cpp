/**
 * Fall 2021 PA 02 Template Repo.
 */
#include "DSString.h"
#include "DSVector.h"
#include "CodeRunner.h"
using namespace std;
/**
 * catch_setup.h and catch_setup.cpp contain the #define directive for
 * the CATCH2 framework.  You can see in main below how I'm calling the
 * runCatchTests() function which is declared in this header.
 *
 * On average, this should reduce the build time for your project on your local
 * machine.
 */
#include "catch_setup.h"
int main(int argc, char** argv) {
    if (argc == 1) {
        runCatchTests();
    }
    else {
        CodeRunner program2;
        DSVector<DSVector<int>> terms;//dsvector of dsvectors. Each term will be a name of its own vector
        DSVector<DSString> wordSort;//used to initially grab terms
        DSString a(argv[1]);//1st command line argument
        DSString b(argv[2]);//2nd command line argument
        DSString c(argv[3]);//3rd command line argument
        program2.readFiles(a, b, wordSort, terms);//reads both files to collect and compare the data
        program2.output(c, wordSort, terms);//final print out to output file
    }
    return 0;
}
