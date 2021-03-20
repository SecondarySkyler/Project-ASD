#include <iostream>
/* normal sum */
int sum(int a, int b){
    return a + b;
}

/* sum by reference */
void sumByRef(int&a, int&b) {
    a += b;
}

/* POINTERS */





int main() {
    int x = 5;
    // int y = 4;
    // int z = sum(x, y);
    // std::cout << "x=" << x << "y=" << y << "z=" << z << std::endl;
    // sumByRef(x, y);
    // std::cout << x << y << std::endl;

    // int *p = &x;
    // int s = *p;
    // std::cout << p << std::endl << s << std::endl;

    int numbers[5]; // number <- puntatore alla prima posizione dell'array in heap
    int * p;
    p = numbers; 
    *p = 10;
    p++; //il puntatore viene spostato sulla casella 1 dell'array
    *p = 20;
    for (int i = 0; i < 5; i++)
    {
        std::cout << numbers[i] << std::endl;
    }
    return 0;
    
}
