#include <iostream>
#include <string.h>
#include "periodProject.hpp"

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

int main() {

    srand(time(NULL));
    string s = generator(50);
    cout << s << endl;
    cout << periodNaive(s) << endl;
    cout << periodSmart(s) << endl; 

    return 0;
}