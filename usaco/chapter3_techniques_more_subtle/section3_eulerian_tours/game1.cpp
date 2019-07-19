/*
ID: wangbb21
LANG: C++
TASK: game1
*/
#include <iostream>
#include <fstream>
using namespace std;

#define max(a, b) (a) > (b) ? (a) : (b)

const int N = 101;
int board[N];
int dp[N][N][2];	// 0 => first; 1 => second

int main() {
    ofstream fout("game1.out");
    ifstream fin("game1.in");
    int n, sum = 0; fin >> n;
	for (int i = 0; i < n; ++i) { 
		fin >> board[i];
		sum += board[i];
		dp[i][i][0] = board[i];
		dp[i][i][1] = 0;
	}
	for (int ln = 2; ln <= n; ++ln) {
		for (int si = 0; si + ln - 1 < n; ++si) {
			int ei = si + ln - 1;
			int sm = board[si] + dp[si + 1][ei][0] + dp[si + 1][ei][1];
			dp[si][ei][0] = max(board[si] + dp[si + 1][ei][1], board[ei] + dp[si][ei - 1][1]);
			dp[si][ei][1] = sm - dp[si][ei][0];
		}
	}
	fout << dp[0][n - 1][0] << " " << dp[0][n - 1][1] << endl;
    fin.close();
    fout.close();
    return 0;
}

