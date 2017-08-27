/*
 * 多重背包问题
 * c[i]：第i件物品的体积
 * w[i]：第i件物品的价值
 * n[i]：第i件物品的数量
 * f[i][v]：前i件物品装在v的背包里能够获得的最大价值
 *
 * 状态转移方程：
 * f[i][v] = max{ f[i-1][v - k*c[i]] + k*w[i] | 0 <= k <= n[i] }
 *
 * 思路：转化为01背包问题
 * 系数取值：1, 2, 4, ..., 2^(k-1), n[i] - 2^k + 1
 */

int N, V;
int c[N], w[N], n[N];
int f[V+1];

int multiple() {
  for (int i = 0; i < N; i++) {
    if (c[i] * n[i] >= V) {
      for (j = c[i]; j <= V; j++) {
        f[j] = max(f[j], f[j-c[i]] + w[i]);
      }
    } else {
      int k = 1, cost, weight, amount = n[i];
      while (k < amount) {
        cost   = k * c[i];
        weight = k * w[i];
        for (j = V; j >= cost; j--) {
          f[j] = max(f[j], f[j - cost] + weight);
        }
        amount -= k;
        k *= 2;
      }
      cost   = amount * c[i];
      weight = amount * w[i];
      for (j = V; j >= cost; j--) {
        f[j] = max(f[j], f[j - cost] + weight);
      }
    }
  }
  return f[V];
}