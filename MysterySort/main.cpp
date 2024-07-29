#include <iostream>
#include <chrono>
#include "include/sorting_library.h"
using namespace std;


int main() {
    //make some data to sort
    const int DATA_SIZE = 500000;
    int d1[DATA_SIZE];
    for (int i = 0; i < DATA_SIZE; i++){
        d1[i] = i;
    }
    int d2[DATA_SIZE];
    int x =0;
    for (int i = DATA_SIZE - 1; i >= 0; i--){
        d2[i] = x;
        x++;
    }
    int d3[DATA_SIZE];
    for (int i = 0; i < DATA_SIZE; i++) {
        d3[i] = rand() % 100000;
    }

    const int DATA_SIZE2 = 100000;
    int c1[DATA_SIZE2];
    for (int i = 0; i < DATA_SIZE2; i++){
        c1[i] = i;
    }
    int c2[DATA_SIZE2];
    x =0;
    for (int i = DATA_SIZE2 - 1; i >= 0; i--){
        c2[i] = x;
        x++;
    }
    int c3[DATA_SIZE2];
    for (int i = 0; i < DATA_SIZE2; i++) {
        c3[i] = rand() % 100000;
    }

    const int DATA_SIZE3 = 10000;
    int b1[DATA_SIZE3];
    for (int i = 0; i < DATA_SIZE3; i++){
        b1[i] = i;
    }
    int b2[DATA_SIZE3];
    x =0;
    for (int i = DATA_SIZE3 - 1; i >= 0; i--){
        b2[i] = x;
        x++;
    }
    int b3[DATA_SIZE3];
    for (int i = 0; i < DATA_SIZE3; i++) {
        b3[i] = rand() % 100000;
    }


    int a1[1000];
    for (int i=0; i<1000;i++){
        a1[i] = i;
    }
    int a2[1000];
    x=0;
    for (int i=999; i>=0;i--){
        a2[i] = x;
        x++;
    }
    int a3[1000];
    for (int i=0; i<1000;i++){
        a3[i] = rand() % 1000;
    }

    cout << fixed << showpoint;
    cout.precision(9);
    print_version_number();

    //just used this layout multiple times to collect data for each mystery function
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    mystery05(a1, 1000);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_in_seconds = end - start;
    std::cout << std::fixed << "Duration: " << time_in_seconds.count() << std::endl;

    std::chrono::time_point<std::chrono::high_resolution_clock> star, en;
    star = std::chrono::high_resolution_clock::now();
    mystery05(a2, 1000);
    en = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_in_second = en - star;
    std::cout << std::fixed << "Duration: " << time_in_second.count() << std::endl;

    std::chrono::time_point<std::chrono::high_resolution_clock> sta, e;
    sta = std::chrono::high_resolution_clock::now();
    mystery05(a3, 1000);
    e = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_in_secon = e - sta;
    std::cout << std::fixed << "Duration: " << time_in_secon.count() << std::endl;
    return 0;
}
