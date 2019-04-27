/**
 * Description: 2D DP
 * Input : m n \n ...
 * Output: maximum value
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int lli;

int main() {
    int m, n;
	lli ans;
	cin >> m >> n;
	vector< vector<lli> > food(m, vector<lli>(n, 0));
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> food[i][j];
		}
	}
	vector< vector<lli> > dp(m, vector<lli>(n, 0));
	vector< vector<bool> > visit(m, vector<bool>(n, false));
	int l = n / 2 - 1, r = n / 2 + 1;
	l = max(l, 0);
	r = min(r, n - 1);
	for (int j = l; j <= r; ++j) {
		dp[m - 1][j] = food[m - 1][j];
		visit[m - 1][j] = true;
	}
	for (int i = m - 2; i >= 0; --i) {
		if (l > 0) 
			l--;
		if (r < n - 1) 
			r++;
		for (int j = l; j <= r; ++j) {
			if (!visit[i + 1][j]) {
				if (j > 0 && visit[i + 1][j - 1]) 
					ans = dp[i + 1][j - 1];
				if (j < n - 1 && visit[i + 1][j + 1]) 
					ans = dp[i + 1][j + 1];
			} else {
				ans = dp[i + 1][j];
				if (j > 0 && visit[i + 1][j - 1]) {
					ans = max(ans, dp[i + 1][j - 1]);
				}
				if (j < n - 1 && visit[i + 1][j + 1]) {
					ans = max(ans, dp[i + 1][j + 1]);
				}
			}
			dp[i][j] = ans + food[i][j];
			visit[i][j] = true;
		}
	}
	ans = dp[0][l];
	for (int i = l + 1; i <= r; ++i) {
		ans = max(ans, dp[0][i]);
	}
	cout << ans << endl;
    return 0;
}

