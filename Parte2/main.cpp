#include <fstream>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "headers/utilities.hpp"
#include "headers/RBT.hpp"

const int a = 1000;
const double max_error = 0.01;
const auto resolution = getResolution();
const double t_min = resolution * ((1 / max_error) + 1);

void calcoloTempi(void);
void calcVar(void);

// compile with g++ -g RBT.cpp utilities.cpp main.cpp -o main
int main(int argc, char **argv) {
    srand(time(NULL));
    calcoloTempi();
    // calcVar();
    std::cout << std::endl;
}

void calcoloTempi() {

    std::ofstream csv(/*treeType + */"RBT.csv"); // csv per la scrittura

    for (int j = 0; j < 100; j++)
    {
        double time;
        int n = a * std::pow(1000, ((j + 0.0)/99)); // calcolo numero elementi
        int iterCount = 0;
        int key = 0;
        std::chrono::steady_clock::time_point end;
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        int insCount;
        do
        {
            RBT tree;
            insCount = 0;
            for (int i = 0; i < n; i++)
            {
                key = (std::rand() * std::rand() % n);

                if (tree.find(key) == nullptr) {
                    tree.insert(key);
                    insCount++;
                }
            }
            end = std::chrono::steady_clock::now();
            iterCount++;
        } while (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < t_min);
        
        std::cout << n << "  Insertions: " + std::to_string(insCount) << std::endl;
        time = ((std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() + 0.0) / iterCount)/n;
        csv << std::to_string(n) << ", " << std::to_string(time) + "\n"; // scrittura su csv 
        std::cout << /*treeType +*/ " Iterazione : " + std::to_string(j) << std::endl;
    }
    std::cout << "Terminato!" << std::endl;
    csv.close();
}

void calcVar() {

    std::ofstream csv(/*treeType + */"RBT_var.csv"); // csv per la scrittura

    for (int j = 0; j < 100; j++)
    {
        for(int iter = 0; iter < 20; iter++)
        {
            RBT tree;
            double time;
            int n = a * std::pow(1000, ((j + 0.0)/99)); // calcolo numero elementi

            int iterCount = 0;
            int key = 0;
            std::chrono::steady_clock::time_point end;
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            do
            {
                for (int i = 0; i < n; i++)
                {
                    if (iterCount == 0) key = (std::rand() * std::rand() % n);
                    if (tree.find(key) == nullptr) tree.insert(key);
                }

                end = std::chrono::steady_clock::now();
                iterCount++;
            } while (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < t_min);
            
            time = ((std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() + 0.0) / iterCount)/n;
            csv << std::to_string(n) << ", " << std::to_string(time) + "\n"; // scrittura su csv 
            std::cout << /*treeType +*/ " Iterazione : " + std::to_string(j) + " SubIter: " + std::to_string(iter+1) << std::endl;
        }
    }
    std::cout << "Terminato!" << std::endl;
    csv.close();
}