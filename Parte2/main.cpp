#include <fstream>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "utilities.hpp"
#include "BST.hpp"
#include "AVL.hpp"


const double max_error = 0.01;
const auto resolution = getResolution();
const double t_min = resolution * ((1 / max_error) + 1);

// compile with g++ -g AVL.cpp BST.cpp utilities.cpp main.cpp -o main
int main(int argc, char **argv) {
    AVL tree;
    tree.insert(20);
    tree.insert(12);
    tree.insert(100);
    tree.inOrder();
    // delete tree;
}

void calcoloTempi(/*treeType*/) {

    std::ofstream avl(/*treeType + */".csv"); // csv per la scrittura

    // Calcolo tempi Naive
    for (int j = 0; j < 100; j++)
    {
        int* k; /* !!! TO ALLOCATE AND DEFINE !!! */
        int iterCount = 0;
        std::chrono::steady_clock::time_point end;
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        do
        {
            /* !!!  INSERT HERE FUNCTION TO MEASURE !!! */
            end = std::chrono::steady_clock::now();
            iterCount++;
        } while (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < t_min);
        
        int t = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / iterCount;
        avl << k[j] << ", " << t << "\n"; // scrittura su csv 
        std::cout << /*treeType +*/ " Iterazione : " +  std::to_string(j) << std::endl;
    }
    avl.close();
}