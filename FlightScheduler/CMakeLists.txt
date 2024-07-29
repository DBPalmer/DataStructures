cmake_minimum_required(VERSION 3.15)
project(22s_flight_planner)

set(CMAKE_CXX_STANDARD 14)

configure_file(data/sample01-flight-data.txt data/sample01-flight-data.txt COPYONLY)
configure_file(data/sample01-req-flights.txt data/sample01-req-flights.txt COPYONLY)

add_executable(22s_flight_planner main.cpp catch_setup.cpp DSLinkedListTest.cpp DSString.cpp DSString.h DSLinkedList.h DSStack.h DSStackTest.cpp City.cpp City.h Flight.cpp Flight.h CodeRunner.cpp CodeRunner.h Route.cpp Route.h DSVector.h)
