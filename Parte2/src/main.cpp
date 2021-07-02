#include <fstream>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <typeinfo>
#include "../headers/utilities.hpp"
#include "../headers/RBT.hpp"
#include "../headers/BST.hpp"
#include "../headers/AVL.hpp"

const int a = 1000;
const double max_error = 0.01;
const auto resolution = getResolution();
const double t_min = resolution * ((1 / max_error) + 1);


template<class T>
std::vector<double> calcoloTempi() {

    std::vector<double> results;
    results.reserve(100); // richiede che il vettore contenga almeno 100 elementi
    
    for (int j = 0; j < 100; j++)
    {
        double tempoAmmortizzato;
        int n = a * std::pow(1000, ((j + 0.0)/99)); // calcolo numero elementi
        int iterCount = 0;
        int key = 0;
        std::chrono::steady_clock::time_point end;
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        do
        {
            T timeTree;
            for (int i = 0; i < n; i++)
            {
                key = std::rand();

                if (timeTree.find(key) == nullptr) {
                    timeTree.insert(key);
                }
            }
            end = std::chrono::steady_clock::now();
            iterCount++;

        } while (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < t_min);

        tempoAmmortizzato = ((std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() + 0.0) / iterCount) / n;

        results.push_back(tempoAmmortizzato);
        std::cout << " Iterazione : " + std::to_string(j) << std::endl;
    }
    
    return results;
}

template<class T>
std::vector<double> calcoloVarianza() {

    std::vector<double> varianze;
    varianze.reserve(100);
    double varianza;
    double averageTime;
    double *arrayOfTimes = new double[20];

    for (int j = 0; j < 100; j++)
    {
        int n = a * std::pow(1000, ((j + 0.0)/99));

        for (int i = 0; i < 20; i++)
        {
            double executionTime;
            int key;
            int iterationsCounter = 0;
            std::chrono::steady_clock::time_point end;
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            do
            {
                T currentTree;
                for (int i = 0; i < n; i++)
                {
                    key = std::rand();
                    if (currentTree.find(key) == nullptr)
                    {
                        currentTree.insert(key);
                    }
                    
                }
                end = std::chrono::steady_clock::now();
                iterationsCounter++;

            } while (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < t_min);

            executionTime = ((std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() + 0.0) / iterationsCounter) / n;
            averageTime += executionTime; 
            arrayOfTimes[i] = executionTime;
            
        }
        averageTime /= 20; // faccio la media dei 20 tempi di esecuzione

        for (int j = 0; j < 20; j++)
        {
            varianza += (arrayOfTimes[j] - averageTime) * (arrayOfTimes[j] - averageTime);
        }
        varianza /= 20;
        varianze.push_back(varianza);
        std::cout << "Iterazione varianza: " << std::to_string(j) << std::endl;
    }
    
    // delete &varianza;
    // delete &averageTime;
    delete[] arrayOfTimes;
    return varianze;  
}


void printRecord(std::vector<double> &bst, std::vector<double> &rbt, std::vector<double> &avl) {
    std::ofstream csv("Records.csv"); // csv per la scrittura
    for (int i = 0; i < bst.size(); i++)    
    {   
        int n = a * std::pow(1000, ((i + 0.0)/99));
        csv << std::to_string(n) <<  " BST, " << bst[i] << ", "
                                    << "RBT, " << rbt[i] << ", "
                                    << "AVL, " << avl[i] << std::endl;
    }
    
}

// compile with g++ -g RBT.cpp utilities.cpp main.cpp -o main
int main(int argc, char **argv) {
    unsigned int seed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    srand(seed);
    
    std::vector<double> tempiBst = calcoloTempi<BST>();
    std::vector<double> tempiRbt = calcoloTempi<RBT>();
    std::vector<double> tempiAvl = calcoloTempi<AVL>();

    // std::vector<double> bst_varianza = calcoloVarianza<BST>();
    // std::vector<double> avl_varianza = calcoloVarianza<AVL>();
    // std::vector<double> rbt_varianza = calcoloVarianza<RBT>();
    printRecord(tempiBst, tempiRbt, tempiAvl);
    // for (int i = 0; i < tempiBst.size(); i++)
    // {
    //     std::cout << tempiBst[i] << ", " << bst_varianza[i] << std::endl;
    // }
    
}