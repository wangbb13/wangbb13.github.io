#include <iostream>
using namespace std;

int g[200000][52] = {0};
int dp[200000] = {0};

int main() {
  int n, k, p, i, j, r, s;
  cin >> n >> k >> p >> i >> j;
  g[0][i]  = 1;
  g[0][50] = j;
  g[0][51] = i;
  for (i = 1; i < n; i++) {
    cin >> j >> r;
    for (s = 0; s < k; s++) {
      g[i][s] = g[i-1][s];
    }
    g[i][j]++;
    g[i][50] = r;
    g[i][51] = j;
  }
  j = g[0][50] <= p ? 0 : (-1);
  for (i = 1; i < n; i++) {
    if (g[i][50] <= p) {
      dp[i] = dp[i-1] + g[i][g[i][51]] - 1;
      j = i;
    } else {
      if (j == -1) {
        dp[i] = dp[i-1];
      } else {
        dp[i] = dp[i-1] + g[j][g[i][51]];
      }
    }
  }
  cout << dp[n-1] << endl;
  return 0;
}