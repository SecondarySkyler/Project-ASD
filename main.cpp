#include <iostream>
#include <vector>
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
const auto resolution {getResolution()};
const double t_min{resolution * ((1 / max_error) + 1)};


int main() {


    std::string generatedStrings [100];
    std::vector<double> naiveTime;
    std::vector<double> smartTime;

    for (int i = 0; i < 100; i++) {
        int n = a * pow(500, i/99); // lunghezza stringa
        generatedStrings[i] = randomString(n);
    }

    // Time for naive 
    for (int j = 0; j < 100; j++)
    {
        steady_clock::time_point start = steady_clock::now();
        periodNaive(generatedStrings[j]);
        steady_clock::time_point end = steady_clock::now();
        naiveTime[j] = duration_cast<nanoseconds>(end - start).count(); 
    }

}