#include <fstream>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <typeinfo>
#include "headers/utilities.hpp"
#include "headers/RBT.hpp"
#include "headers/BST.hpp"
#include "headers/AVL.hpp"

const int a = 1000;
const double max_error = 0.01;
const auto resolution = getResolution();
const double t_min = resolution * ((1 / max_error) + 1);

// template<class T>
// std::vector<std::pair<double, double>> calcoloTempi(T tree) {

//     std::vector<std::pair<double, double>> results;
//     std::ofstream csv( ((std::string) typeid(tree).name()).substr(1, 3) + ".csv"); // csv per la scrittura
    
//     for (int j = 0; j < 100; j++)
//     {
//         double tempoAmmortizzato;
//         int n = a * std::pow(1000, ((j + 0.0)/99)); // calcolo numero elementi
//         int iterCount = 0;
//         int key = 0;
//         std::chrono::steady_clock::time_point end;
//         std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
//         // int insCount;
//         do
//         {
//             T tree;
//             // insCount = 0;
//             for (int i = 0; i < n; i++)
//             {
//                 key = std::rand();

//                 if (tree.find(key) == nullptr) {
//                     tree.insert(key);
//                     // insCount++;
//                 }
//             }
//             end = std::chrono::steady_clock::now();
//             iterCount++;
//         } while (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < t_min);

//         double var = calcVar(n);
        
//         // std::cout << n << "  Insertions: " + std::to_string(insCount) << std::endl;
//         tempoAmmortizzato = ((std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() + 0.0) / iterCount) / n;
//         results.push_back(std::make_pair(tempoAmmortizzato, var));
//         csv << std::to_string(n) << ", " << std::to_string(tempoAmmortizzato) + "\n"; // scrittura su csv 
//         std::cout << /*treeType +*/ " Iterazione : " + std::to_string(j) << std::endl;
//     }
//     std::cout << "Terminato!" << std::endl;
//     csv.close();
//     return results;
// }


/*
* CALCOLO VARIANZA
*/
template<class T>
std::vector<std::pair<double, double>> calcVar(T tree) {

    std::vector<std::pair<double, double>> result;
    
    for (int j = 0; j < 100; j++)
    {
        double var;
        double averageTime;
        double arrayOfTimes[20];
        int n;
        for(int iter = 0; iter < 20; iter++)
        {
            double tempoAmmortizzato;
            n = a * std::pow(1000, ((j + 0.0)/99)); // calcolo numero elementi

            int iterCount = 0;
            int key = 0;
            std::chrono::steady_clock::time_point end;
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            do
            {
                T tree;
                for (int i = 0; i < n; i++)
                {
                    if (iterCount == 0) key = (std::rand());
                    if (tree.find(key) == nullptr) tree.insert(key);
                }

                end = std::chrono::steady_clock::now();
                iterCount++;
            } while (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < t_min);
            
            tempoAmmortizzato = ((std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() + 0.0) / iterCount)/n;
            averageTime += tempoAmmortizzato;
            arrayOfTimes[iter] = tempoAmmortizzato;

            std::cout << /*treeType +*/ " Iterazione : " + std::to_string(j) + " SubIter: " + std::to_string(iter+1) << std::endl;
        }
        averageTime /= 20;
        for (int i = 0; i < 20; i++)
        {
            var += (arrayOfTimes[i] - averageTime) * (arrayOfTimes[i] - averageTime);
        }
        var /= 20;
        result.push_back(std::make_pair(averageTime, var));
        
    }
    std::cout << "Terminato!" << std::endl;
    return result;
}

void printRecord(std::vector<std::pair<double, double>> bst, std::vector<std::pair<double, double>> rbt, std::vector<std::pair<double, double>> avl) {
    std::ofstream csv("Records.csv"); // csv per la scrittura
    for (int i = 0; i < bst.size(); i++)    
    {   
        int n = a * std::pow(1000, ((i + 0.0)/99));
        csv << std::to_string(n) <<  "BST, " << bst[i].first << ", " << bst[i].second << ", "
                                    << "RBT, " << rbt[i].first << ", " << rbt[i].second << ", "
                                    << "AVL, " << avl[i].first << ", " << avl[i].second << std::endl;
    }
    
}

// compile with g++ -g RBT.cpp utilities.cpp main.cpp -o main
int main(int argc, char **argv) {
    srand(time(NULL));
    BST bst_tree;
    AVL avl_tree;
    RBT rbt_tree;
    
    std::vector<std::pair<double, double>> tempiBst = calcVar(bst_tree);
    std::vector<std::pair<double, double>> tempiAvl = calcVar(avl_tree);
    std::vector<std::pair<double, double>> tempiRbt = calcVar(rbt_tree);
    printRecord(tempiBst, tempiRbt, tempiAvl);
    // calcVar();
}