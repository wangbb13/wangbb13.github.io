/**
 * Description: fetch numbers in grids
 * Input : N * N
 * Output: ...
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10;
int input[N][N];
int dp[N][N][N][N];

int main() {
    int n, x, y, v;
	cin >> n;
	while (true) {
		cin >> x >> y >> v;
		if (x == 0 && y == 0 && v == 0) break;
		input[x - 1][y - 1] = v;
	}
	dp[0][1][1][0] = input[0][1] + input[1][0];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int a = 0; a < n; ++a) {
				for (int b = 0; b < n; ++b) {
					if (i != a && j != b) {
						int ans = input[i][j] + input[a][b];
						int max_val = 0;
						int i0 = i - 1, j0 = j - 1;
						int a0 = a - 1, b0 = b - 1;
						if (i0 >= 0 && a0 >= 0) max_val = max(max_val, dp[i0][j][a0][b]);
						if (i0 >= 0 && b0 >= 0 && i0 != a && j != b0) max_val = max(max_val, dp[i0][j][a][b0]);
						if (j0 >= 0 && a0 >= 0 && i != a0 && j0 != b) max_val = max(max_val, dp[i][j0][a0][b]);
						if (j0 >= 0 && b0 >= 0) max_val = max(max_val, dp[i][j0][a][b0]);
						dp[i][j][a][b] = ans + max_val;
					}
				}
			}
		}
	}
	cout << input[0][0] + input[n - 1][n - 1] + dp[n - 1][n - 2][n - 2][n - 1] << endl;
    return 0;
}

