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

// array con puntatori alle funzioni per generare le stringhe
typedef string (*genMethods)(int);
genMethods gen_methods[4] = {&randomString, &randomQ, &randomChar, &worstCase}; 


// prototipi delle funzioni
void generateStrings(int);
int *fillLengthArray();
void calcoloTempi(int);
void calcVar(int);
void calcDistribution(int, int);

// per compilare g++ periodFinal.cpp main.cpp -o main
int main(int argc, char **argv) {
    srand(time(NULL));

    if (argc > 1) {
        if (isInArray("--1", argv, argc)) {
            calcoloTempi(0);
        } 
        if (isInArray("--2", argv, argc)) {
            calcoloTempi(1);
        }
        if (isInArray("--3", argv, argc)) {
            calcoloTempi(2);
        }
        if (isInArray("--4", argv, argc)) {
            calcoloTempi(3);
        }
        if (isInArray("--var", argv, argc)) {
            calcVar(2);
        }
        if (isInArray("--distr", argv, argc))
        {
            calcDistribution(100, 500);
        }
    } 
}

/**
 * Metodo che genera 100 stringhe di lunghezza diversa
 * memorizzate in un array passato come argomento
 */
void generateStrings(int method, string array[]) {
    for (int i = 0; i < 100; i++) {
        int n = a * pow(500, ((i + 0.0)/99)); // lunghezza stringa
        array[i] = gen_methods[method](n);
    }
}

/**
 * Metodo per riempire un array con le lunghezze delle stringhe
 * array[0] = 1000
 * array[99] = 500.000
 */
int* fillLengthArray() {
    static int arrayOfLength[100];
    for (int i = 0; i < 100; i++)
    {
        arrayOfLength[i] = (int) a * pow(500, ((i + 0.0)/99));
    }
    return arrayOfLength;   
}

/**
 * Metodo per il calcolo dei tempi di esecuzione dei due algoritmi
 * @method e' il numero del metodo che si vuole utilizzare per la generazione delle stringhe
 */
void calcoloTempi(int method) {
    
    string generatedStrings[100];
    generateStrings(method, generatedStrings);

    ofstream naive_first("naive_" + to_string(method) + ".csv"); // csv per la scrittura
    ofstream smart_first("smart_" + to_string(method) + ".csv"); // csv per la scrittura

    // Calcolo tempi Naive
    for (int j = 0; j < 100; j++)
    {

        int iterCount = 0;
        steady_clock::time_point end;
        steady_clock::time_point start = steady_clock::now();
        do
        {
            periodNaive(generatedStrings[j]);
            end = steady_clock::now();
            iterCount++;
        } while (duration_cast<nanoseconds>(end - start).count() < t_min);
        
        naiveTime[j] = duration_cast<nanoseconds>(end - start).count() / iterCount;
        naive_first << generatedStrings[j].length() << ", " << naiveTime[j] << "\n"; // scrittura su csv 
        cout << "Naive -- Metodo: " + to_string(method) << " Iterazione : " +  to_string(j) << endl;
    }
    naive_first.close();


    // Calcolo tempi Smart
    for (int j = 0; j < 100; j++)
    {
        int iterCount = 0;
        steady_clock::time_point end = steady_clock::now();
        steady_clock::time_point start = steady_clock::now();
        do
        {
            periodSmart(generatedStrings[j]);
            end = steady_clock::now();
            iterCount++;
        } while (duration_cast<nanoseconds>(end - start).count() < t_min);
        
        smartTime[j] = duration_cast<nanoseconds>(end - start).count() / iterCount;
        smart_first << generatedStrings[j].length() << ", " << smartTime[j] << "\n"; // scrittura su csv
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
            int iterCount = 0;
            steady_clock::time_point end = steady_clock::now();
            steady_clock::time_point start = steady_clock::now();
            do
            {
                periodNaive(s);
                end = steady_clock::now();
                iterCount++;
            } while (duration_cast<nanoseconds>(end - start).count() < t_min);

            naiveTime[j] = duration_cast<nanoseconds>(end - start).count() / iterCount;
            iterations++;
            naive_var << s.length() << ", " << naiveTime[j] << "\n";  
            cout << "Naive_Var ~"  << " Lunghezza(n°): " +  to_string(j) + " Iterazione: " + to_string(iterations) << endl;
        } while (iterations < 20);
        

        iterations = 0;

        do
        {
            string s = gen_methods[1](arrayOfLength[j]);
            int iterCount = 0;
            steady_clock::time_point end = steady_clock::now();
            steady_clock::time_point start = steady_clock::now();
            do
            {
                periodSmart(s);
                end = steady_clock::now();
                iterCount++;
            } while (duration_cast<nanoseconds>(end - start).count() < t_min);

            smartTime[j] = duration_cast<nanoseconds>(end - start).count() / iterCount;
            iterations++;
            smart_var << s.length() << ", " << smartTime[j] << "\n"; 
            cout << "Smart_Var ~" << " Lunghezza(n°): " +  to_string(j) << " Iterazione: " + to_string(iterations) << endl;
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
        
        for (int j = 0; j < iterations; j++)
        {
            string s = gen_methods[i](length); // genero la stringa
            periodOccurencies[periodSmart(s)]++; // aumento di 1 il valore in posizione periodSmart(s)
        }

        for (int z = 0; z < length + 1; z++)
        {
            distribution << to_string(z) << ", " << to_string(periodOccurencies[z]) << "\n";
        }
        distribution.close();
        free(periodOccurencies);
    }
}