#include "CodeRunner.h"
void CodeRunner::readFlightFile(DSString file, DSLinkedList<City>& cities, DSLinkedList<Flight>& flights) {
    ifstream flightFile;
    flightFile.open(file.c_str());
    if (!flightFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    int x;
    flightFile >> x;//number of lines in file
    char d[1000];
    char air[1000];
    double cost, time;
    int z = 0;
    flightFile.getline(d, 100);//skips to the next line after x
    while (z < x){//runs until end of file is reached
        flightFile.getline(d, 100, ' ');
        DSString name(d);//name of city
        City city1(name);
        flightFile.getline(d, 100, ' ');
        DSString name2(d);//name of city
        City city2(name2);
        if (cities.search(city1) == false){//will not add if it already exhists inside
            if (city1.getCities().search(city2) == false) {//will not add if it already exhists inside
                city1.push(city2);
            }
            cities.push_back(city1);
        }
        else {
            if (cities.find(city1).getCities().search(city2) == false) {//searches inside cities for the city
                cities.find(city1).push(city2);
            }
        }
        if (cities.search(city2) == false){//will not add if it already exhists inside
            if (city2.getCities().search(city1) == false) {//will not add if it already exhists inside
                city2.push(city1);
            }
            cities.push_back(city2);
        }
        else {
            if (cities.find(city2).getCities().search(city1) == false) {//searches inside cities for the city
                cities.find(city2).push(city1);
            }
        }
        flightFile >> cost;
        flightFile.getline(d, 100, ' ');//skips to next line
        flightFile >> time;
        flightFile.getline(d, 100, ' ');//skips to next line
        flightFile.getline(air, 100);//airline name
        DSString airline(air);
        Flight flight(city1, city2, airline, cost, time);//collects all the data into a flight object
        flights.push_back(flight);//adds flight to flights
        Flight flight2(city2, city1, airline, cost, time);//we know that the fight goes both ways, so we can add the returning flight as well
        flights.push_back(flight2);//adds flight to flights
        z++;
    }
    flightFile.close();
}
void CodeRunner::readReqFileAndOutput(DSString file, DSString file2, DSLinkedList<City>& cities, DSLinkedList<Flight>& flights){
    DSLinkedList<DSLinkedList<City>> paths;//use to capture iterative backtracking
    ifstream reqFile;
    reqFile.open(file.c_str());
    if (!reqFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    ofstream outFile;
    outFile.open(file2.c_str());//opening file with name passed in
    if (!outFile.is_open()) {//checks if file can open
        cout << "File failed to open." << endl;
    }
    int x;
    char d[1000];
    reqFile >> x;//number of lines in file
    int z =0;
    reqFile.getline(d, 100);//skips to the next line after x
    while (z < x){//runs until end of file is reached
        reqFile.getline(d, 100, ' ');
        DSString srce(d);//source city name
        City source(srce);
        reqFile.getline(d, 100, ' ');
        DSString dest(d);//destination city name
        City destination(dest);
        reqFile.getline(d, 100);
        DSString type(d);//cost or time
        paths = iterBacktrack(source, destination, cities);//finds possible paths based on source and destination
        outFile << source.getName() << ", " << destination.getName();
        if (type == "T"){
            outFile << " (Time)" << endl;
        }
        else {
            outFile << " (Cost)" << endl;
        }
        if (&paths.getHead() == nullptr){//will check if it is event possible before output results
                outFile << "    ERROR: no flights available to connect the two cities\n\n";//error msg
        }
        else {
            outputResults(type, findRoutes(paths, flights), outFile);//will then output routes based on cost or time
        }
        z++;
    }
    reqFile.close();
    outFile.close();
}
DSLinkedList<DSLinkedList<City>> CodeRunner::iterBacktrack(City& source, City& dest, DSLinkedList<City>& cities){
    DSLinkedList<DSLinkedList<City>> routes;
    DSStack<City> stack;
    City* curr;
    City possDest;
    stack.push(cities.find(source));//STEP 1
    cities.reset();
    while (cities.hasElement()) {
        cities.getElement().data.getCities().reset();//resets all the iterators
        cities.getNext();
    }
    curr = &stack.peek();//poiner so that iterator will not reset
    possDest = stack.peek();//used to see if final dest is reached
    while (stack.is_empty() == false){//STEP 2
        if (possDest == dest){//STEP 3
            DSLinkedList<City> path(stack.getList());//save path
            routes.push_back(path);//adds successful path to routes
            stack.pop();//removes last element
            possDest = stack.peek();
            curr = &stack.peek();
        }
        else {
            if (curr->getCities().hasElement() == true) {//"IS CONNECTION NULL?"
                if (stack.search(curr->getCities().getElement().data) == false) {//"IS CONNECTION ON THE STACK?"
                    stack.push(cities.find(curr->getCities().getElement().data));//add element to stack
                    possDest = cities.find(curr->getCities().getElement().data);
                    curr->getCities().getNext();
                    curr = &stack.peek();
                }
                else {
                    //possDest = curr.getCities().getElement().data;
                    curr->getCities().getNext();
                }
            } else {
                curr->getCities().reset();//reset curr itr since end of LL is reached
                stack.pop();//remove curr from stack
                if (&stack.peek() != nullptr) {//causes errors if stack is empty
                    possDest = stack.peek();
                    curr = &stack.peek();
                }
            }
        }
    }
    return routes;//return all possible routes
}
DSLinkedList<DSLinkedList<Flight>> CodeRunner::findRoutes(DSLinkedList<DSLinkedList<City>>& paths, DSLinkedList<Flight>& flights) {
    DSLinkedList<DSLinkedList<Flight>> routes;
    DSLinkedList<Flight> flhts;
    Flight flight;
    paths.reset();
    while (paths.hasElement()) {//collects the highest amount of flight options for one set of two cities
        int best = 0;
        paths.getElement().data.reset();
        while (paths.getElement().data.hasElement()) {
            int x = 0;
            if (paths.getElement().data.getElement().next != nullptr) {//have to check since flight needs two cities
                flhts = findLegs(flights, paths.getElement().data.getElement().data,paths.getElement().data.getElement().next->data);
                flhts.reset();
                while (flhts.hasElement()) {
                    x++;//counts the number of flights available
                    flhts.getNext();
                }
                if (x > best) {//will take the highest #, then us it down below
                    best = x;
                }
            }
            paths.getElement().data.getNext();
        }
        int z = 0;
        while (z < best) {//will run as many times until the one with the most options is reached
            paths.getElement().data.reset();
            z++;
            DSLinkedList<Flight> leg;
            while (paths.getElement().data.hasElement()) {
                if (paths.getElement().data.getElement().next != nullptr) {//have to check since flight needs to cities
                    flight = findLeg(flights, paths.getElement().data.getElement().data,paths.getElement().data.getElement().next->data,z);//finds all the possible flights from the two cities
                    leg.push_back(flight);//pushes flight that was taken at an index of z
                }
                paths.getElement().data.getNext();
            }
            routes.push_back(leg);//each leg represents a possible sequence of flights
        }
        paths.getNext();
    }
    return routes;
}
DSLinkedList<Flight> CodeRunner::findLegs(DSLinkedList<Flight>& flights, City& source, City& dest){
    DSLinkedList<Flight> legs;//stored in a LL since there are multiple flights with different airlines
    flights.reset();
    while(flights.hasElement()){
        if (flights.getElement().data.getCityA() == source && flights.getElement().data.getCityB() == dest){//find the flights from the two cities passed by iterating through the flight LL
            legs.push_back(flights.getElement().data);
        }
        flights.getNext();
    }
    return legs;//return LL of flights
}
Flight CodeRunner::findLeg(DSLinkedList<Flight>& flights, City& source, City& dest, int& loc){
    flights.reset();
    int max=0;
    while(flights.hasElement()) {
        if (flights.getElement().data.getCityA() == source && flights.getElement().data.getCityB() == dest) {//find the flights from the two cities passed by iterating through the flight LL
           max++;
        }
        flights.getNext();
    }
    flights.reset();
    int use;//the number that will actually be used below
    if (max < loc){//cant be higher than max, otherwise it won't return anything, but still has to be called for the other flights with more airline options
        use = max;
    }
    else {
        use = loc;
    }
    int x=0;
    while(flights.hasElement()) {
        if (flights.getElement().data.getCityA() == source && flights.getElement().data.getCityB() == dest) {//find the flights from the two cities passed by iterating through the flight LL
            x++;
            if (x == use) {//only if this is the location I am looking for
                return flights.getElement().data;//returns specific flight
            }
        }
        flights.getNext();
    }
}
void CodeRunner::outputResults(DSString type, DSLinkedList<DSLinkedList<Flight>> routes, basic_ofstream<char>& outFile){
    DSLinkedList<Route> sortedRoutes;//stored the routes and ouputs them in order
    DSVector<int> ints;//used for sorting functionality
    routes.reset();
    while(routes.hasElement()) {//while loop to calc and capture necessary time and price ints
        routes.getElement().data.reset();
        int time = 0;
        int price = 0;
        while (routes.getElement().data.hasElement()) {
            price += routes.getElement().data.getElement().data.getCost();
            time += routes.getElement().data.getElement().data.getTime();
            if (routes.getElement().data.getElement().prev != nullptr){
                if (routes.getElement().data.getElement().prev->data.getAirline() == routes.getElement().data.getElement().data.getAirline()){
                }
                else {//if changed airlines
                    time += 27;
                }//if this has a layover
                time += 43;
                price += 23;
            }
            routes.getElement().data.getNext();
        }
        Route rte(routes.getElement().data, price, time);//creates route object
        if (type == "T"){//sorts based on type passed in by user
            ints.push_back(time);
        }
        if (type == "C"){//sorts based on type passed in by user
            ints.push_back(price);
        }
        sortedRoutes.push_back(rte);
        routes.getNext();
    }
    ints.sort();//sorts elements in ints
    int stop = 0;
    if(ints.getSize() > 3){//will make sure to print a max of 3
        stop = 3;
    }
    else {//otherwise, will print ints size
        stop = ints.getSize();
    }
    DSNode<Route> *itr;//keeps track of loc when ints has same number variables
    for (int i = 0; i < stop; i++) {
        sortedRoutes.reset();
        while (sortedRoutes.hasElement()) {
            if (type == "T") {
                if (sortedRoutes.getElement().data.getTime() == ints[i]) {//if element is what we are looking for
                    if (itr != &sortedRoutes.getElement()) {// and only if it has not been added yet
                        itr = &sortedRoutes.getElement();//make new itr
                        outFile << "Itinerary " << i + 1 << ": \n";
                        sortedRoutes.getElement().data.getRoute().reset();
                        while (sortedRoutes.getElement().data.getRoute().hasElement()) {//print format
                            outFile << "    "
                                    << sortedRoutes.getElement().data.getRoute().getElement().data.getCityA().getName()
                                    << "->"
                                    << sortedRoutes.getElement().data.getRoute().getElement().data.getCityB().getName()
                                    << " ("
                                    << sortedRoutes.getElement().data.getRoute().getElement().data.getAirline()
                                    << ")\n";
                            sortedRoutes.getElement().data.getRoute().getNext();
                        }
                        outFile << "    Totals for itinerary " << i + 1 << ": Time: "
                                << sortedRoutes.getElement().data.getTime() << " Cost: "
                                << sortedRoutes.getElement().data.getCost() << endl;
                        if (i < ints.getSize() - 1) {//needed since i could be out of range
                            if (ints[i] == ints[i + 1]) {//if at a place where the next element in ints is the same, need to move to sortedRoutes next
                                sortedRoutes.getNext();
                            }
                        }
                    }
                }
            }
            if (type == "C") {
                if (sortedRoutes.getElement().data.getCost() == ints[i]) {//if element is what we are looking for
                    if (itr != &sortedRoutes.getElement()) {// and only if it has not been added yet
                        itr = &sortedRoutes.getElement();
                        outFile << "Itinerary " << i + 1 << ": \n";
                        sortedRoutes.getElement().data.getRoute().reset();
                        while (sortedRoutes.getElement().data.getRoute().hasElement()) {//print format
                            outFile << "    "
                                    << sortedRoutes.getElement().data.getRoute().getElement().data.getCityA().getName()
                                    << "->"
                                    << sortedRoutes.getElement().data.getRoute().getElement().data.getCityB().getName()
                                    << " ("
                                    << sortedRoutes.getElement().data.getRoute().getElement().data.getAirline()
                                    << ")\n";
                            sortedRoutes.getElement().data.getRoute().getNext();
                        }
                        outFile << "    Totals for itinerary " << i + 1 << ": Cost: "
                                << sortedRoutes.getElement().data.getCost() << " Time: "
                                << sortedRoutes.getElement().data.getTime() << endl;
                        if (i < ints.getSize() - 1) {//needed since i could be out of range
                            if (ints[i] == ints[i + 1]) {//if at a place where the next element in ints is the same, need to move to sortedRoutes next
                                sortedRoutes.getNext();
                            }
                        }
                    }
                }
            }
            sortedRoutes.getNext();
        }
    }
    outFile << endl;
}