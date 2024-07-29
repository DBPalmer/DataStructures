#ifndef INC_22S_FLIGHT_PLANNER_CODERUNNER_H
#define INC_22S_FLIGHT_PLANNER_CODERUNNER_H
#include <iostream>
#include <fstream>
#include "DSLinkedList.h"
#include "DSStack.h"
#include "Flight.h"
#include "City.h"
#include "Route.h"
#include "DSVector.h"

class CodeRunner {
public:
    /**
     * reads flights to create adjList and list of Flights
     */
    void readFlightFile(DSString, DSLinkedList<City>&, DSLinkedList<Flight>&);
    /**
     * reads requests and then performs backtracking and flight search for those paths
     */
    void readReqFileAndOutput(DSString, DSString, DSLinkedList<City>&, DSLinkedList<Flight>&);
    /**
     * exhaustively searches for paths from City to City
     * @return LL of the the possible LL paths
     */
    DSLinkedList<DSLinkedList<City>> iterBacktrack(City&, City&, DSLinkedList<City>&);
    /**
     * for all possible sources, returns flights needed to get to destination
     * @return LL of possible flight paths from source to destination
     */
    DSLinkedList<DSLinkedList<Flight>> findRoutes(DSLinkedList<DSLinkedList<City>>&, DSLinkedList<Flight>&);
    /**
     * finds flights from one city to the next, knowing that those two cities have at least one connecting flight
     * @return LL of flights from City to City
     */
    DSLinkedList<Flight> findLegs(DSLinkedList<Flight>&, City&, City&);
    /**
     * same functionality as above, just pulls one at a specific location
     * @return Flight
     */
    Flight findLeg(DSLinkedList<Flight>&, City&, City&, int&);
    /**
     * calculates price and time and outputs findings to output file
     */
    void outputResults(DSString, DSLinkedList<DSLinkedList<Flight>>, basic_ofstream<char>&);
};


#endif //INC_22S_FLIGHT_PLANNER_CODERUNNER_H
