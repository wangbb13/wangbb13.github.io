/*
ID: wangbb21
LANG: C++
TASK: kimbits
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

const int MAXN = 31;
long long C[MAXN][MAXN];
long long dp[MAXN + 1][MAXN + 1];

int main() {
    ofstream fout("kimbits.out");
    ifstream fin("kimbits.in");
    int N, L;
	long long l;
	fin >> N >> L >> l;
	// C_n_m
	for (int i = 0; i < N; ++i) {
		C[i][0] = 1;
		int upper = min(i, L);
		for (int j = 1; j <= upper; ++j) {
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}
	// dp 
	for (int i = 1; i <= N; ++i) {
		dp[i][0] = 1;
		int upper = min(L, i - 1);
		for (int j = 1; j <= upper; ++j) {
			dp[i][j] = dp[i][j - 1] + C[i - 1][j];
		}
	}
	// calc
	int j = L;
	for (int i = N; i > 0; --i) {
		j = min(i - 1, j);
		if (l > dp[i][j]) {
			fout << 1;
			l -= dp[i][j];
			j--;
		} else {
			fout << 0;
		}
	}
	fout << endl;
    fin.close();
    fout.close();
    return 0;
}

