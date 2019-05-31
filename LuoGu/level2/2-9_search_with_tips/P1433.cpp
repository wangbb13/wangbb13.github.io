/**
 * Description: eat cheese 
 * Input : n \n (xi, yi) .. 
 * Output: minimum distance 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

#define min(a, b) ((a) < (b) ? (a) : (b))

const int N = 16;
struct _pos {
    double x, y;
} pos[N];

double dist[N][N];
bool visit[N];

void dfs(int pi, int cs, double dis, int n, double& ans) {
    if (dis > ans) 
        return;
    if (cs == n) {
        ans = min(ans, dis);
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (visit[i]) {
            visit[i] = false;
            dfs(i, cs + 1, dis + dist[pi][i], n, ans);
            visit[i] = true;
        }
    }
}

void sc_dp(int n, double& max_val) {
	int s = 1 << n;
	vector< vector<double> > dp(n, vector<double>(s, max_val));
	for (int i = 1; i < s; ++i) {
		for (int j = 0; j < n; ++j) {
			if ((i & (1 << j)) == 0) continue; 
			if (i == (1 << j)) { 
				dp[j][i] = 0.0;
				continue;
			}
			for (int k = 0; k < n; ++k) {
				if ((i & (1 << k)) == 0 || j == k) continue; 
				dp[j][i] = min(dp[j][i], dp[k][i - (1 << j)] + dist[k + 1][j + 1]);
			}
		}
	}
	for (int i = 0; i < n; ++i) 
		max_val = min(max_val, dp[i][s - 1] + dist[0][i + 1]);
}

int main() {
    int n;
    cin >> n;
    double ans = 0.0;
    pos[0].x = pos[0].y = 0.0;
    for (int i = 1; i <= n; ++i) 
        cin >> pos[i].x >> pos[i].y;
    n++;
    int len = n * (n - 1) / 2;
    for (int i = 0; i < n; ++i) {
        visit[i] = true;
        for (int j = i + 1; j < n; ++j) {
            double dx = pos[i].x - pos[j].x;
            double dy = pos[i].y - pos[j].y;
            dist[i][j] = sqrt(dx * dx + dy * dy);
            dist[j][i] = dist[i][j];
        }
        if (i + 1 < n)
            ans += dist[i][i + 1];
    }
    visit[0] = false;
    // dfs(0, 1, 0.0, n, ans);
    sc_dp(n - 1, ans);
	printf("%.2f\n", ans);
    return 0;
}

