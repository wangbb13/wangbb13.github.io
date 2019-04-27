/**
 * Description: pass slips, two ways
 * Input : m n \n the matrix of favorable degree
 * Output: maximum favorable degree
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 50;

int seat[N][N] = {0};
int dp[N][N][N][N] = {0};

int main() {
    int m, n, ans = 0;
	cin >> m >> n;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> seat[i][j];
			ans += seat[i][j];
		}
	}
	if (m == 1 || n == 1) {
		cout << ans << endl;
		return 0;
	}
	dp[1][0][0][1] = dp[0][1][1][0] = seat[1][0] + seat[0][1];
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int x = 0; x < m; ++x) {
				for (int y = 0; y < n; ++y) {
					if (i != x && j != y && dp[i][j][x][y] == 0 && dp[x][y][i][j] == 0) {
						ans = 0;
						if ((i > 0) && (x > 0)) {
							ans = max(ans, dp[i - 1][j][x - 1][y]);
						}
						if ((i > 0) && (y > 0) && (i - 1 != x) && (y - 1 != j)) {
							ans = max(ans, dp[i - 1][j][x][y - 1]);
						}
						if ((j > 0) && (y > 0)) {
							ans = max(ans, dp[i][j - 1][x][y - 1]);
						}
						if ((j > 0) && (x > 0) && (j - 1 != y) && (x - 1 != i)) {
							ans = max(ans, dp[i][j - 1][x - 1][y]);
						}
						dp[i][j][x][y] = max(dp[i][j][x][y], seat[i][j] + seat[x][y] + ans);
					}
				}
			}
		}
	}
	cout << max(dp[m - 1][n - 2][m - 2][n - 1], dp[m - 2][n - 1][m - 1][n - 2]) << endl;
    return 0;
}

