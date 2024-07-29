#ifndef INC_22S_FLIGHT_PLANNER_CITY_H
#define INC_22S_FLIGHT_PLANNER_CITY_H
#include "DSLinkedList.h"
#include "DSString.h"
using namespace std;
class City {
private:
    DSString name;
    DSLinkedList<City> cities;
public:
    /**
     * constructors and destructor
     */
    City();
    City(DSString&);
    City(const City&);
    ~City();
    /**
     * needed so that cities can be compared to cities, especially in DS LL find()
     * @return the actual city in adjList with its own LL inside
     */
    City& operator=(const City&);
    /**
     * compares only the name of the city, used for search and find functions
     * @return bool
     */
    bool operator==(const City&);
    /**
     * wrapper of DSLL's push_back()
     */
    void push(City&);
    /**
     * @return name
     */
    DSString& getName();
    /**
     * @return LL of city connections
     */
    DSLinkedList<City>& getCities();
};
#endif //INC_22S_FLIGHT_PLANNER_CITY_H
