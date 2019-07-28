/*
ID: wangbb21
LANG: C++
TASK: nuggets
*/
#include <iostream>
#include <fstream>
using namespace std;

// Solution 1 Note: 
// The only way for there to be no bound to the largest number 
// which is unobtainable is if the greatest common divisor of the 
// package sizes is greater than 1. 
//
// Solution 2 Note:
// Given two relatively prime numbers N and M, the largets number 
// that you cannot make is N * M - N - M. So the answer cannot 
// exceed 256 * 256 - 256 - 256 = 65024. Naive DP is enough. 

int gcd(int a, int b) {
	int temp;
	while (b != 0) {
		temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}

int main() {
    ofstream fout("nuggets.out");
    ifstream fin("nuggets.in");
    // 
    fin.close();
    fout.close();
    return 0;
}

