#include <fstream>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <typeinfo>
#include <array>
#include "../headers/utilities.hpp"
#include "../headers/RBT.hpp"
#include "../headers/BST.hpp"
#include "../headers/AVL.hpp"

const int a = 1000;
const double max_error = 0.01;
const auto resolution = getResolution();
const double t_min = resolution * ((1 / max_error) + 1);


template<class T>
double calcoloVarianza(std::vector<double> &vectorOfKeys, int n) {

    double varianza {0.0};
    double averageTime {0.0};
    std::array<double, 20> arrayOfTimes;

    // for (int j = 0; j < 100; j++)
    // {
        // int n = a * std::pow(1000, ((j + 0.0)/99));

        for (int i = 0; i < 20; i++)
        {
            double executionTime;


            int iterationsCounter = 0;
            std::chrono::steady_clock::time_point end;
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            do
            {
                T currentTree;
                for (const auto &key : vectorOfKeys)
                {
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

        for (const auto &time : arrayOfTimes)
        {
            varianza += pow((time - averageTime), 2);
        }
        varianza /= 20;
    // }
    
    return varianza;  
}

template<class T>
std::pair<double, double> calcoloTempi(std::vector<double> &vectorOfKeys, int n) {

    std::pair<double, double> results;
    
    // for (int j = 0; j < 100; j++)
    // {
        double tempoAmmortizzato;
        // int n = a * std::pow(1000, ((j + 0.0)/99)); // calcolo numero elementi
        int iterCount = 0;

        std::chrono::steady_clock::time_point end;
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

        do
        {
            T timeTree;

            for (const auto &key : vectorOfKeys)
            {
                if (timeTree.find(key) == nullptr) {
                    timeTree.insert(key);
                }
            }
            end = std::chrono::steady_clock::now();
            iterCount++;

        } while (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < t_min);

        tempoAmmortizzato = ((std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() + 0.0) / iterCount) / n;
        double varianza = calcoloVarianza<T>(vectorOfKeys, n);

        results = std::make_pair(tempoAmmortizzato, varianza); // sarebbe da eseguire un make_pair 

    // }
    
    return results;
}



void printRecordCsv(std::vector<std::pair<double, double>> &bst, std::vector<std::pair<double, double>> &rbt, std::vector<std::pair<double, double>> &avl) {
    std::ofstream csv("Records.csv"); // csv per la scrittura
    for (int i = 0; i < bst.size(); i++)    
    {   
        int n = a * std::pow(1000, ((i + 0.0)/99));
        csv << std::to_string(n) <<  ", " << "BST, " << bst[i].first << ", " << bst[i].second << ", " 
                                          << "RBT, " << rbt[i].first << ", " << rbt[i].second << ", "
                                          << "AVL, " << avl[i].first << ", " << avl[i].second << ", " << "\n";
    }
    
}

void fillVectorWithNodes(std::vector<double> &keysVector, int n) {
    for (int h = 0; h < n; h++)
    {
        keysVector.push_back(std::rand());
    }
}

void fillVectorWorstCase(std::vector<double> &vector, int n) {
    for (int h = 0; h < n; h++)
    {
        vector.push_back(h);
    }    
}

// compile with g++ -g RBT.cpp utilities.cpp main.cpp -o main
int main(int argc, char **argv) {
    unsigned int seed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    srand(seed);

    std::vector<std::pair<double, double>> tempi_varianza_bst;
    tempi_varianza_bst.reserve(100);

    std::vector<std::pair<double, double>> tempi_varianza_avl;
    tempi_varianza_avl.reserve(100);

    std::vector<std::pair<double, double>> tempi_varianza_rbt;
    tempi_varianza_rbt.reserve(100);

    for (int i = 0; i < 100; i++)
    {
        int n = a * std::pow(1000, ((i + 0.0) / 99));
        std::vector<double> keys;
        keys.reserve(n);
        fillVectorWithNodes(keys, n);

        auto bst_result = calcoloTempi<BST>(keys, n);
        auto avl_result = calcoloTempi<AVL>(keys, n);
        auto rbt_result = calcoloTempi<RBT>(keys, n);

        tempi_varianza_bst.push_back(bst_result);
        tempi_varianza_avl.push_back(avl_result);
        tempi_varianza_rbt.push_back(rbt_result);   
    }

    // for (int j = 0; j < tempi_varianza_bst.size(); j++)
    // {
    //     std::cout << "BST, " << tempi_varianza_bst[j].first << " " << tempi_varianza_bst[j].second << " " 
    //               << "AVL, " << tempi_varianza_avl[j].first << " " << tempi_varianza_avl[j].second << " "
    //               << "RBT, " << tempi_varianza_rbt[j].first << " " << tempi_varianza_rbt[j].second << "\n"; 
    // }
    
    
    printRecordCsv(tempi_varianza_bst, tempi_varianza_rbt, tempi_varianza_avl);

    
}