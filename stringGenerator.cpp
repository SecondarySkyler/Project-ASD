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

// int periodIterative(string s) {
//     // int n = s.length();
    
//     // NOTA BENE: TUTTI GLI INDICI PARTONO DA 1!!!
//     // es. s[1] primo carattere
//     // s = s[1...n]

//     // r := alloca vettore di n elementi (indicizzati da 1 a n)
//     // r[i] dovrebbe rappresentare il 
//     // primo/max bordo di s[1...i]
    
//     // r[1] = 0 
    
//     for (int i = 1; i < n; i++) {
//         // calcolare il primo/max bordo di s[1...i+1]
//         // usando i valori r(1), r(2), ..., r(i)
        
//         // 1) prima devo cercare *un* bordo z
//         //    di s[1...i] che soddisfi
//         //    s[i+1] = s[z+1]
//         //    e z dev'essere massimo

//         z = r[i] // z è primo/max bordo di s[1...i]
//         while (s[i+1] != s[z+1]) && (z > 0) {
//             // Nota: per ogni j <= i, 
//             // r(j) è primo/max bordo di s[1...j]
//             // s[1...z] è il bordo corrente

//             // Quindi il bordo successivo dev'essere
//             // il bordo del bordo corrente!...
//             z = r[z];

//             // adesso z è il bordo successivo (piu' corto!) 
//         }
//         // ababab....ababab
//             j   z         
//         // s = ababaabababab  
        /**
         * r(1) = 0
         * r(2) = 0 
         * r(3) =>  (r(2) ?= r(2) + 1) => no (r(r(2))) = 1
         * r(4) = r(3) == r(3) + 1 => falso r(r(3)) = 2
         * r(5) = r(4) == r(4) + 1 => falso r(5) = 3
         * r(6) = 1
         * 
         * 
         * */
    //     if (s[i+1] == s[z+1])
    //         r[i+1] := z + 1;
    //     else
    //         r[i+1] := 0;
    // }
    
    // // r(n) e' primo/max bordo di s[1...n] = s
    // return n - r(n); // periodo frazionario minimo
// }

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

int main() {
    srand(time(NULL));
    // string prova = "abcabcab";
    // string gen = generator(100);
    // int i = periodNaive(gen);
    // double res = getResolution();
    string s = "ababaabababab";
    int res = periodSmart(s);
    std::cout << res << std::endl;    
}