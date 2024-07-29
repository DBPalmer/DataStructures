#include "Flight.h"
Flight::Flight(){
}
Flight::Flight(City& cit1, City& cit2, DSString& air, double& cst, double& tme){//sets all the data, used when reading flight file
    a = cit1;
    b = cit2;
    airline = air;
    cost = cst;
    time = tme;
}
bool Flight::operator==(const Flight& flight){
    if (a==flight.a && b==flight.b && airline==flight.airline && cost==flight.cost && time==flight.time){//if all variable are equal
        return true;
    }
    else {
        return false;
    }
}
City& Flight::getCityA(){
    return a;
}
City& Flight::getCityB(){
    return b;
}
DSString& Flight::getAirline(){
    return airline;
}
double& Flight::getCost(){
    return cost;
}
double& Flight::getTime(){
    return time;
}