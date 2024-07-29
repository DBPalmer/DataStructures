#include "Route.h"
Route::Route(){
}
Route::Route(DSLinkedList<Flight>& rte, int cst, int tme){//sets all the data, used when reading route of flights
    cost = cst;
    time = tme;
    route = rte;
}
int& Route::getCost(){
    return cost;
}
int& Route::getTime(){
    return time;
}
DSLinkedList<Flight>& Route::getRoute(){
    return route;
}