/*
ID: wangbb21
LANG: C++
TASK: butter
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int inf = 0xffff;

int main() {
    ofstream fout("butter.out");
    ifstream fin("butter.in");
    int N, P, C, ans = 0;
	fin >> N >> P >> C;
	vector< vector<int> > pasture(P + 1, vector<int>(P + 1, inf));
	vector<int> cow(N + 1);
	for (int i = 1; i <= N; ++i) 
		fin >> cow[i];
	int sp, tp, wp;
	for (int i = 0; i < C; ++i) {
		fin >> sp >> tp >> wp;
		pasture[sp][tp] = pasture[tp][sp] = wp;
		ans += wp;
	}
	for (int k = 1; k <= P; ++k) {
		for (int i = 1; i <= P; ++i) {
			for (int j = 1; j <= P; ++j) {
				if (i == j) {
					pasture[i][j] = 0;
					continue;
				}
				pasture[i][j] = min(pasture[i][j], pasture[i][k] + pasture[k][j]);
			}
		}
	}
	for (int i = 1; i <= P; ++i) {
		int one = 0;
		for (int j = 1; j <= N; ++j) 
			one += pasture[i][cow[j]];
		ans = min(ans, one);
	}
	fout << ans << endl;
    fin.close();
    fout.close();
    return 0;
}

