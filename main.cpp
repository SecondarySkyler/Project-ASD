#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
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
string generatedStrings[100];
double naiveTime[100];
double smartTime[100];


typedef string (*genMethods)(int);
genMethods gen_methods[4] = {&randomString, &randomQ, &randomChar, &worstCase}; 



void generateStrings(int);
void calcoloTempi(int);

// per compilare g++ periodFinal.cpp main.cpp -o main
int main(int argc, char **argv) {
    srand(time(NULL));

    
    if (argc > 1) {
        if (strcmp(argv[1], "--1") == 0) {
            calcoloTempi(0);
        } 
        if (strcmp(argv[2], "--2") == 0) {
            calcoloTempi(1);
        }
        if (strcmp(argv[3], "--3") == 0) {
            calcoloTempi(2);
        }
        if (strcmp(argv[4], "--4") == 0) {
            calcoloTempi(4);
        }
    }
    

    




    // steady_clock::time_point start = steady_clock::now();
    // periodSmart(generatedStrings[0]);
    // steady_clock::time_point end = steady_clock::now();
    // smartTime[0] = duration_cast<nanoseconds>(end - start).count();


    // cout << gen_methods[0](5) << endl;
    // cout << argc << endl;
    // cout << argv[0] << " " << argv[1] << endl; 


    // std::cout << generatedStrings[0].length() << std::endl;
    // std::cout << generatedStrings[99].length() << std::endl;
    // std::cout << naiveTime[0] << std::endl;
    // std::cout << smartTime[0] << std::endl;
    

}


void generateStrings(int method) {
    for (int i = 0; i < 100; i++) {
        int n = a * pow(500, ((i + 0.0)/99)); // lunghezza stringa
        generatedStrings[i] = gen_methods[method](n);
    }
}

void calcoloTempi(int method) {
    generateStrings(method);

    ofstream naive_first("naive_" + to_string(method) + ".csv");
    ofstream smart_first("smart_" + to_string(method) + ".csv");

    // Time for naive 
    for (int j = 0; j < 100; j++)
    {
        steady_clock::time_point start = steady_clock::now();
        periodNaive(generatedStrings[j]);
        steady_clock::time_point end = steady_clock::now();
        double elapsedTime = duration_cast<nanoseconds>(end - start).count(); 
        int iterCount = 1;
        while (elapsedTime < t_min)
        {
            start = steady_clock::now();
            periodNaive(generatedStrings[j]);
            end = steady_clock::now();
            elapsedTime += duration_cast<nanoseconds>(end - start).count(); 
            iterCount++;
        }
        naiveTime[j] = elapsedTime / iterCount;
        naive_first << generatedStrings[j].length() << ", " << naiveTime[j] << "\n";    
    }
    naive_first.close();


    // Time smart
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
        generatedStrings[j].clear();   
    }
    smart_first.close();
}