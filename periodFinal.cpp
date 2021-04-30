#include <iostream>
// #include <string.h>
#include <chrono>
#include "periodFinal.hpp"

using namespace std::chrono;
using namespace std;


int periodSmart(string s) {
    s = " " + s;
    int n = s.length();

    int r[n];

    r[1] = 0; // primo/max bordo di s[1...1]
    n--;
    for (int i = 1; i < n - 1; i++) {
        int z = r[i];
        while (s[i+1] != s[z+1] && z > 0) {
            z = r[z];
        }

        if (s[i+1] == s[z+1])
            r[i+1] = z + 1;
        else
            r[i+1] = 0;
    }
    return n - r[n - 1];
}

int periodNaive (string s) { 
    for (int p = 1; p <= s.length(); p++) { 
        string s1 = s.substr(0, s.length() - p); 
        string s2 = s.substr(p, s.length() - p); 
        if (s1.compare(s2) == 0) 
            return p;
    }
    return s.length();
}

// METODO 1
string randomString(int n) {
    string s = "";
    for (int i = 0; i < n; i++) {
        s += (std::rand() % 2) + 'a';
    }
    return s;
}

// METODO 2
string randomQ(int n) {
    int q = std::rand() % n + 1; // 1 - n
    string s = randomString(q);
    for (int i = q; i < n; i++) {
        s += s[(i % q)];
    }
    return s;
    // 10
    // q = abca
    // s = abc => abcabc => abcabcabc => abcabcabca
}

// METODO 3
string randomChar(int n) {
    int q = std::rand() % n + 1;
    string s = randomString(q);
    s[q - 1] = 'c'; 
    for (int i = q; i < n; i++) {
        s += s[(i % q)];
    }
    return s;
}

// METODO 4
string worstCase(int n) {
    int q = n - 1;
    string s = randomString(q);
    for (int i = q; i < n; i++) {
        s += s[(i % q)];
    }
    return s;
}

double getResolution() {
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;
    do {
        end = steady_clock::now();
    } while (start == end);
    typedef duration<double, nanoseconds::period> duration;
    return duration_cast<nanoseconds>(end - start).count();
}

