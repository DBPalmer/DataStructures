#ifndef INC_22S_FLIGHT_PLANNER_ROUTE_H
#define INC_22S_FLIGHT_PLANNER_ROUTE_H
#include "DSLinkedList.h"
#include "Flight.h"
class Route {
private:
    DSLinkedList<Flight> route;
    int cost;
    int time;
public:
    /**
     * constructor
     */
    Route();
    Route(DSLinkedList<Flight>&, int, int);
    /**
     * getters
     * @return private data
     */
    int& getCost();
    int& getTime();
    DSLinkedList<Flight>& getRoute();
};


#endif //INC_22S_FLIGHT_PLANNER_ROUTE_H
