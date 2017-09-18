/*
 * 01背包问题
 * c[i]：第i件物品的体积
 * w[i]：第i件物品的价值
 * f[i][v]：前i件物品装在v的背包里能够获得的最大价值
 * 状态转移方程（最基本的，最重要的）：
 * f[i][v] = max(f[i-1][v], f[i-1][v-c[i]] + w[i])
 */


int N, V;

int c[N], w[N];
int f[N+1][V+1];
int ff[V+1];

// 未优化空间复杂度
int version0() {
  for (int i = 0; i <= V; i++) {
    f[0][i] = 0;
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 0; j <= V; j++) {
      dp[i][j] = dp[i-1][j];
      if (j >= c[i-1]) {
        dp[i][j] = max(dp[i][j], dp[i-1][j-c[i-1]] + w[i-1]);
      }
    }
  }
  return dp[N][V];
}

// 优化空间复杂度
int version1() {
  for (int i = 0; i < N; i++) {
    for (int j = V; j >= c[i]; j--) {
      dp[j] = max(dp[j], dp[j-c[i]] + w[i]);
    }
  }
  return dp[V];
}