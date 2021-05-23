#include <fstream>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utilities.hpp"
#include "BST.hpp"
#include "AVL.hpp"

const int a = 1000000;
const double max_error = 0.01;
const auto resolution = getResolution();
const double t_min = resolution * ((1 / max_error) + 1);

void calcoloTempi(BST);

// compile with g++ -g AVL.cpp BST.cpp utilities.cpp main.cpp -o main
int main(int argc, char **argv) {
    BST tree;
    calcoloTempi(tree);
    std::cout << std::endl;
}

void calcoloTempi(BST tree) {

    std::ofstream csv(/*treeType + */"BST.csv"); // csv per la scrittura

    for (int j = 0; j < 100; j++)
    {
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
                if (iterCount == 0) key = std::rand();
                if (tree.find(key) == NULL) tree.insert(key);
            }

            end = std::chrono::steady_clock::now();
            iterCount++;
        } while (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < t_min);
        
        time = ((std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() + 0.0) / iterCount)/n;
        csv << std::to_string(n) << ", " << std::to_string(time) + "\n"; // scrittura su csv 
        std::cout << /*treeType +*/ " Iterazione : " + std::to_string(j) << std::endl;
    }
    csv.close();
}