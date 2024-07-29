#ifndef INC_22S_FLIGHT_PLANNER_FLIGHT_H
#define INC_22S_FLIGHT_PLANNER_FLIGHT_H
#include "City.h"
#include "DSString.h"
using namespace std;
class Flight {
private:
    City a;
    City b;
    DSString airline;
    double cost;
    double time;
public:
    /**
     * constructors
     */
    Flight();
    Flight(City&, City&, DSString&, double&, double&);
    /**
     * equality operator
     * @return bool
     */
    bool operator==(const Flight&);
    /**
     * getters
     * @return private data
     */
    City& getCityA();
    City& getCityB();
    DSString& getAirline();
    double& getCost();
    double& getTime();
};


#endif //INC_22S_FLIGHT_PLANNER_FLIGHT_H
