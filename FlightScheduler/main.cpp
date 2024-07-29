/**
 * Fall 2021 PA 04 - Flight Planner Template Repo.
 * Based on PA 02 Template repo
 */
#include "catch_setup.h"
#include "DSString.h"
#include "DSLinkedList.h"
#include "City.h"
#include "Flight.h"
#include "CodeRunner.h"
using namespace std;
int main(int argc, char** argv) {
    if(argc == 1) {
        runCatchTests();
    }
    else {
        DSLinkedList<City> adjList;//adjacency list: each city has its own private linked lists
        DSLinkedList<Flight> flights;//all possible flights with airline, time, and cost
        DSString flghtFle(argv[1]);
        DSString reqFle(argv[2]);
        DSString outFile(argv[3]);
        CodeRunner PA04;
        PA04.readFlightFile(flghtFle, adjList, flights);//reads the flights and captures adjList and Flights
        PA04.readReqFileAndOutput(reqFle, outFile, adjList, flights);//gets requested paths and outputs findings
    }
    return 0;
}