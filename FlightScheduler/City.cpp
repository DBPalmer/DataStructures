#include "City.h"
City::City(){
}
City::City(DSString& nme){
    name = nme;//DSString operator=
}
City::City(const City& cit){
    name = cit.name;//DSString operator=
    cities = cit.cities;//DSLL operator=
}
City::~City(){
    //nothing necessary, dsstring and dslinkedlist have their own destructors
}
City& City::operator=(const City& cit){
    name = cit.name;//DSString operator=
    cities = cit.cities;//DSLL operator=
    return *this;
}
bool City::operator==(const City& cit){
    return (name == cit.name);//vague, but will come in handy during the search, find, and comparisons
}
void City::push(City& city) {
    cities.push_back(city);//DSLL functionality
}
DSString& City::getName() {
    return name;
}
DSLinkedList<City>& City::getCities() {
    return cities;
}