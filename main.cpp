#include <iostream>
#include <vector>
#include <fstream>
// #include <string.h>
#include <cmath>
#include <array>
#include <chrono>
using namespace std::chrono;
using namespace std;

#include "periodFinal.hpp"

const int a = 1000;
const double b = pow(500, 1/99);
const double max_error = 0.001;
const auto resolution = getResolution();
const double t_min = resolution * ((1 / max_error) + 1);
// ofstream naive_first("naive_first.csv");
ofstream smart_first("smart_first.csv");


int main() {

    // per compilare g++ periodFinal.cpp main.cpp -o main

    std::string generatedStrings[100];
    double naiveTime[100];
    double smartTime[100];

    for (int i = 0; i < 100; i++) {
        int n = a * pow(500, ((i + 0.0)/99)); // lunghezza stringa
        generatedStrings[i] = randomString(n);
    }

    std::cout << t_min << std::endl;
    // Time for naive 
    // for (int j = 0; j < 100; j++)
    // {
    //     steady_clock::time_point start = steady_clock::now();
    //     periodNaive(generatedStrings[j]);
    //     steady_clock::time_point end = steady_clock::now();
    //     double elapsedTime = duration_cast<nanoseconds>(end - start).count(); 
    //     int iterCount = 1;
    //     while (elapsedTime < t_min)
    //     {
    //         start = steady_clock::now();
    //         periodNaive(generatedStrings[j]);
    //         end = steady_clock::now();
    //         elapsedTime += duration_cast<nanoseconds>(end - start).count(); 
    //         iterCount++;
    //     }
    //     naiveTime[j] = elapsedTime / iterCount;
    //     naive_first << generatedStrings[j].length() << ", " << naiveTime[j] << "\n";    
    // }
    // naive_first.close();


    for (int j = 0; j < 100; j++)
    {
        steady_clock::time_point start = steady_clock::now();
        periodSmart(generatedStrings[j]);
        steady_clock::time_point end = steady_clock::now();
        double elapsedTime = duration_cast<nanoseconds>(end - start).count(); 
        int iterCount = 1;
        while (elapsedTime < t_min)
        {
            start = steady_clock::now();
            periodSmart(generatedStrings[j]);
            end = steady_clock::now();
            elapsedTime += duration_cast<nanoseconds>(end - start).count(); 
            iterCount++;
        }
        smartTime[j] = elapsedTime / iterCount;
        smart_first << generatedStrings[j].length() << ", " << smartTime[j] << "\n";    
    }
    smart_first.close();


    // steady_clock::time_point start = steady_clock::now();
    // periodSmart(generatedStrings[0]);
    // steady_clock::time_point end = steady_clock::now();
    // smartTime[0] = duration_cast<nanoseconds>(end - start).count();

    // std::cout << (sizeof(generatedStrings) / sizeof(*generatedStrings)) << std::endl;

    // std::cout << generatedStrings[0].length() << std::endl;
    // std::cout << generatedStrings[99].length() << std::endl;
    // std::cout << naiveTime[0] << std::endl;
    // std::cout << smartTime[0] << std::endl;
    

}