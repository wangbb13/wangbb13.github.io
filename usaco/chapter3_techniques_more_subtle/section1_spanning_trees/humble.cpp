/*
ID: wangbb21
LANG: C++
TASK: humble
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ofstream fout("humble.out");
    ifstream fin("humble.in");
    int K, N;
    fin >> K >> N;
    vector<int> primes(K);
    for (int i = 0; i < K; ++i) 
        fin >> primes[i];
    vector<int> pointers(K, 0);
    vector<int> humbles(N + 1, 0);
    humbles[0] = 1;
    // PAY ATTENTION: Integer OVERFLOW !!
    for (int i = 1; i <= N; ++i) {
        humbles[i] = primes[0] * humbles[pointers[0]];
        for (int j = 1; j < K; ++j) 
            humbles[i] = min(humbles[i], primes[j] * humbles[pointers[j]]);
        if (i == N) 
            break;
        for (int j = 0; j < K; ++j) {
            int temp = primes[j] * humbles[pointers[j]];
            while (temp > 0 && temp <= humbles[i]) {
                pointers[j]++;
                temp = primes[j] * humbles[pointers[j]];
            }
        }
    }
    fout << humbles[N] << endl;
    fin.close();
    fout.close();
    return 0;
}
