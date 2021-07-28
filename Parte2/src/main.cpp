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

/**
 * Metodo per popolare un vettore con chiavi generate in modo pseudo casuale
 * 
 * **/
void fillVectorWithNodes(std::vector<double> &keysVector, int n) {
    for (int h = 0; h < n; h++)
    {
        keysVector.push_back(std::rand());
    }
}

/**
 * Metodo per popolare un vettore con chiavi generate in modo deterministico
 * Usato per la verifica del caso pessimo
 * **/
void fillVectorWorstCase(std::vector<double> &vector, int n) {
    for (int h = 1; h <= n; h++)
    {
        vector.push_back(h);
    }    
}

/**
 * Metodo per il calcolo della varianza
 * il parametro n è la dimensione del set di nodi da generare
 * la varianza è ottenuta iterando per 20 volte le operazioni di inserimento/ricerca
 * sul set di n nodi, a ogn iterazione il set viene rigenerato  
 **/
template<class T>
double calcoloVarianza(int n) {

    double varianza {0.0};
    double averageTime {0.0};
    std::array<double, 20> arrayOfTimes;

        for (int i = 0; i < 20; i++)
        {
            double executionTime;
            std::vector<double> keys;  
            keys.reserve(n);
            fillVectorWithNodes(keys, n); // popolo il vettore con n nodi

            int iterationsCounter = 0;
            std::chrono::steady_clock::time_point end;
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            do
            {
                T currentTree;
                for (const auto &key : keys)
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
    
    return varianza;  
}

template<class T>
double calcoloTempi(std::vector<double> &vectorOfKeys, int n) {

    double tempoAmmortizzato;
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

    return tempoAmmortizzato;
}



void printRecordCsv(std::vector<std::pair<double, double>> &bst, std::vector<std::pair<double, double>> &rbt, std::vector<std::pair<double, double>> &avl) {
    std::ofstream csv("Records_tempo_varianza.csv"); // csv per la scrittura
    for (int i = 0; i < bst.size(); i++)    
    {   
        int n = a * std::pow(1000, ((i + 0.0)/99));
        csv << std::to_string(n) <<  ", " << "BST, " << bst[i].first << ", " << bst[i].second << ", " 
                                          << "RBT, " << rbt[i].first << ", " << rbt[i].second << ", "
                                          << "AVL, " << avl[i].first << ", " << avl[i].second << ", " << "\n";
    } 
    csv.close();  
}

void printWorstCaseCsv(std::vector<double> &bst, std::vector<double> &rbt, std::vector<double> &avl) {
    std::ofstream csv("Records_tempo_worst_bst.csv"); // csv per la scrittura
    for (int i = 0; i < bst.size(); i++)
    {
        int n = a * std::pow(1000, ((i + 0.0)/99));
        csv << std::to_string(n) << ", " << "BST, " << bst[i] << "\n";
    }
    csv.close();
    
    std::ofstream csv2("Records_tempo_worst_rbt&avl.csv");
    for (int i = 0; i < rbt.size(); i++)
    {
        int n = a * std::pow(1000, ((i + 0.0)/99));
        csv2 << std::to_string(n) << ", " << "RBT, " << rbt[i] << ", " << "AVL, " << avl[i] << "\n"; 
    }
    csv2.close();
}


// compile with g++ -g RBT.cpp utilities.cpp main.cpp -o main
int main(int argc, char **argv) {
    unsigned int seed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    srand(seed);

    std::vector<std::pair<double, double>> tempi_varianza_bst; // contiene tempi ammortizzati e varianze BST
    tempi_varianza_bst.reserve(100);

    std::vector<std::pair<double, double>> tempi_varianza_avl; // contiene tempi ammortizzati e varianze AVL
    tempi_varianza_avl.reserve(100);

    std::vector<std::pair<double, double>> tempi_varianza_rbt; // contiene tempi ammortizzati e varianze RBT
    tempi_varianza_rbt.reserve(100);

    for (int i = 0; i < 100; i++)
    {
        int n = a * std::pow(1000, ((i + 0.0) / 99));
        std::vector<double> keys;
        keys.reserve(n);
        fillVectorWithNodes(keys, n); // popolo il vettore dei nodi di modo che le n operazioni avvengano sullo stesso set per i 3 alberi

        std::cout << std::to_string(i) << std::endl;

        tempi_varianza_bst.push_back(std::make_pair(calcoloTempi<BST>(keys, n), calcoloVarianza<BST>(n)));
        tempi_varianza_avl.push_back(std::make_pair(calcoloTempi<AVL>(keys, n), calcoloVarianza<AVL>(n)));
        tempi_varianza_rbt.push_back(std::make_pair(calcoloTempi<RBT>(keys, n), calcoloVarianza<RBT>(n)));   

    }

    std::vector<double> tempoWorstCaseBst;
    tempoWorstCaseBst.reserve(100);

    std::vector<double> tempoWorstCaseAvl;
    tempoWorstCaseAvl.reserve(100);

    std::vector<double> tempoWorstCaseRbt;
    tempoWorstCaseRbt.reserve(100);

    for (int z = 0; z < 100; z++)
    {
        std::cout << "Worst case bst/avl/rbt iteration " + std::to_string(z) << "\n";
        int n = a * std::pow(1000, ((z + 0.0) / 99));
        std::vector<double> keys;
        keys.reserve(100);
        fillVectorWorstCase(keys, n);

        if(n < 200000) {
            tempoWorstCaseBst.push_back(calcoloTempi<BST>(keys, n));   
        }

        tempoWorstCaseAvl.push_back(calcoloTempi<AVL>(keys, n));
        tempoWorstCaseRbt.push_back(calcoloTempi<RBT>(keys, n));
    }
    
    printRecordCsv(tempi_varianza_bst, tempi_varianza_rbt, tempi_varianza_avl);
    printWorstCaseCsv(tempoWorstCaseBst, tempoWorstCaseRbt, tempoWorstCaseAvl);

}