/*
ID: wangbb21
LANG: C++
TASK: range
*/
#include <iostream>
#include <fstream>
using namespace std;

#define min(a, b) (a) < (b) ? (a) : (b)

const int N = 251;
int dp[N][N];
int stat[N];

int main() {
    ofstream fout("range.out");
    ifstream fin("range.in");
    int n, lu;
	char ch;
	fin >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			fin >> ch;
			if (ch == '1') dp[i][j] = 1;
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (dp[i][j] == 0) continue;
			lu = n;
			if (i > 0 && j > 0) lu = min(lu, dp[i - 1][j - 1]); else lu = 0;
			if (i > 0) lu = min(lu, dp[i - 1][j]); else lu = 0;
			if (j > 0) lu = min(lu, dp[i][j - 1]); else lu = 0;
			if (lu < n) dp[i][j] = lu + 1;
			for (int k = 2; k <= dp[i][j]; ++k) stat[k]++;
		}
	}
	for (int i = 2; i <= n; ++i) 
		if (stat[i] > 0) 
			fout << i << " " << stat[i] << endl;
    fin.close();
    fout.close();
    return 0;
}

