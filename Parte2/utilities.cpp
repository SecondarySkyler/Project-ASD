#include <string.h>
#include <chrono>
#include "headers/utilities.hpp"

double getResolution() {
    std::chrono::steady_clock::time_point end;
    std::chrono::steady_clock::time_point start;
    long sum = 0;
    for (int i = 0; i < 50; i++) {
        start = std::chrono::steady_clock::now();
        do {
            end = std::chrono::steady_clock::now();
        } while (start == end);
        typedef std::chrono::duration<double, std::chrono::nanoseconds::period> duration;
        sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    return (sum+0.0)/50;
}

bool isInArray(char *s, char **array, int argc) {
    bool check = false;
    for(int i = 1; i<argc; i++) {
        check |= !strcmp(array[i], s);
    }
    return check;
}