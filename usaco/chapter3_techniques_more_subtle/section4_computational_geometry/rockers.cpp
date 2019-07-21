/*
ID: wangbb21
LANG: C++
TASK: rockers
*/
#include <iostream>
#include <fstream>
using namespace std;

#define max(a, b) (a) > (b) ? (a) : (b)

const int N = 401;
int dp[N];

int d_i(int i, int dv) {
	int ans = i / dv;
	if (i % dv == 0) return ans;
	return ans + 1;
}

int main() {
    ofstream fout("rockers.out");
    ifstream fin("rockers.in");
    int N, T, M, V, sl;
	fin >> N >> T >> M;
	V = M * T;
	for (int i = 1; i <= V; ++i) dp[i] = -1;
	for (int i = 0; i < N; ++i) {
		fin >> sl;
		if (sl > T) continue;
		for (int v = V; v > sl; --v) {
			int lv = v - sl;
			int ldi = d_i(lv, T);
			int rdi = d_i(v, T);
			if (ldi == rdi && dp[lv] >= 0) 
				dp[v] = max(dp[v], dp[lv] + 1);
			if (ldi + 1 == rdi && v >= ldi * T + sl) {
				int pre = -1, upper = ldi * T;
				for (int j = (ldi - 1) * T + 1; j <= upper; ++j) 
					pre = max(dp[j], pre);
				if (pre >= 0)
					dp[v] = max(dp[v], pre + 1);
			}
		}
		dp[sl] = max(dp[sl], 1);
	}
	int ans = 0;
	for (int i = 1; i <= V; ++i) 
		ans = max(ans, dp[i]);
	fout << ans << endl;
    fin.close();
    fout.close();
    return 0;
}

