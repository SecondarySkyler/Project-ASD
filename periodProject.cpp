#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
using std::string;
using namespace std;
using namespace std::chrono;

int periodNaive (string s) { 
    for (int p = 1; p <= s.length(); p++) { 
        string s1 = s.substr(0, s.length() - p); 
        string s2 = s.substr(p, s.length() - p); 
        if (s1.compare(s2) == 0) 
            return p;
    }
    return s.length();
}

int periodSmart (string s) {
    int n = s.size();

    int r[n];
    r[1] = 0;   //primo/max bordo di s[1...1]

    for (int i = 1; i < n; i++) {
        // s[1...i] che soddisfi => s[i+1] = s[z+1]
        // s[2] = s[1]
        int z = r[i];
        while (s[i + 1] != s[z + 1] && z > 0) {
            z = r[z];
        }
        if (s[i+1] == s[z+1])
            r[i+1] = z + 1;
        else
            r[i+1] = 0;
        
    }
    return r[n - 1];
    
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

string generator(int n) {
    
    int samplesNum = n * 100000;
    string s(n, 'a');

    for (int i = 0; i < samplesNum; i++) {
        
        int q = ((int) rand()) % n + 1;

        for (int j = 0; j < q; j++) {
            s[j] = 'a' + ((int) rand()) % 2;
        }
        for (int j = q; j < n; j++) {   
            s[j] = s[j % q];
        }
           
    }
    return s;
}