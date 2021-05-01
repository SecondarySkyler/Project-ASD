#include <iostream>
#include <stdlib.h>
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

double naiveTime[100];
double smartTime[100];
int stringsLength[100]; // array per le lunghezze delle stringhe


typedef string (*genMethods)(int);
genMethods gen_methods[4] = {&randomString, &randomQ, &randomChar, &worstCase}; 



void generateStrings(int);
int *fillLengthArray();
void calcoloTempi(int);
void calcVar(int);
void calcDistribution(int, int);

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
            calcoloTempi(3);
        }
        if (strcmp(argv[5], "--var") == 0) {
            calcVar(2);
        }
        if (strcmp(argv[6], "--distr") == 0)
        {
            calcDistribution(100, 500);
        }  
    }

    // for (int i = 0; i < 100; i++)
    // {
    //     int n = a * pow(500, ((i + 0.0)/99));
    //     string s = worstCase(n);
    //     cout << periodSmart(s) << endl;
    // }
    
}


void generateStrings(int method, string array[]) {
    for (int i = 0; i < 100; i++) {
        int n = a * pow(500, ((i + 0.0)/99)); // lunghezza stringa
        array[i] = gen_methods[method](n);
        cout << i << endl;
    }
}

int* fillLengthArray() {
    static int arrayOfLength[100];
    for (int i = 0; i < 100; i++)
    {
        arrayOfLength[i] = (int) a * pow(500, ((i + 0.0)/99));
    }
    return arrayOfLength;   
}

void calcoloTempi(int method) {
    
    string generatedStrings[100];
    generateStrings(method, generatedStrings);

    ofstream naive_first("naive_" + to_string(method) + ".csv");
    ofstream smart_first("smart_" + to_string(method) + ".csv");

    // // Time for naive 
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
        cout << "Naive -- Metodo: " + to_string(method) << " Iterazione : " +  to_string(j) << endl;
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
        cout << "Smart -- Metodo: " + to_string(method) << " Iterazione : " +  to_string(j) << endl;  
    }
    smart_first.close(); 
}

void calcVar(int method) {
    int *arrayOfLength = fillLengthArray();

    ofstream naive_var("var_naive_" + to_string(method) + ".csv");
    ofstream smart_var("var_smart_" + to_string(method) + ".csv");

    
    int iterations = 0;
    for (int j = 0; j < 100; j++)
    {
        do
        {   
            string s = gen_methods[1](arrayOfLength[j]);
            steady_clock::time_point start = steady_clock::now();
            periodNaive(s);
            steady_clock::time_point end = steady_clock::now();
            double elapsedTime = duration_cast<nanoseconds>(end - start).count(); 
            int iterCount = 1;
            while (elapsedTime < t_min)
            {
                start = steady_clock::now();
                periodNaive(s);
                end = steady_clock::now();
                elapsedTime += duration_cast<nanoseconds>(end - start).count(); 
                iterCount++;
            }
            naiveTime[j] = elapsedTime / iterCount;
            iterations++;
            naive_var << s.length() << ", " << naiveTime[j] << "\n";  
            cout << "Naive_Var -- Metodo: 2"  << " Ciclo : " +  to_string(j) << " Iterazione: " + to_string(iterations) << endl;
        } while (iterations < 20);
        

        iterations = 0;

        do
        {
            string s = gen_methods[1](arrayOfLength[j]);
            steady_clock::time_point start = steady_clock::now();
            periodSmart(s);
            steady_clock::time_point end = steady_clock::now();
            double elapsedTime = duration_cast<nanoseconds>(end - start).count(); 
            int iterCount = 1;
            while (elapsedTime < t_min)
            {
                start = steady_clock::now();
                periodSmart(s);
                end = steady_clock::now();
                elapsedTime += duration_cast<nanoseconds>(end - start).count(); 
                iterCount++;
            }
            smartTime[j] = elapsedTime / iterCount;
            iterations++;
            smart_var << s.length() << ", " << smartTime[j] << "\n"; 
            cout << "Smart_Var -- Metodo: 2" << " Ciclo : " +  to_string(j) << " Iterazione: " + to_string(iterations) << endl;
        } while (iterations < 20);
        iterations = 0;
    }  
    naive_var.close();  
    smart_var.close();
}


void calcDistribution(int length, int iterations) {

    for (int i = 0; i < 4; i++) {
        int *periodOccurencies;
        periodOccurencies = (int*) calloc(length + 1, sizeof(int));

        ofstream distribution("distribution_method" + to_string(i + 1) + ".csv");
        distribution << "Period" << ", " << "Occurencies" << "\n";
        
        for (int j = 0; j < iterations; j++)
        {
            string s = gen_methods[i](length);
            periodOccurencies[periodSmart(s)]++;
        }

        for (int i = 0; i < length + 1; i++)
        {
            distribution << to_string(i) << ", " << to_string(periodOccurencies[i]) << "\n";
        }
        distribution.close();
    }
}