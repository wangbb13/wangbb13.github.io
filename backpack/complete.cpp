/*
 * 完全背包问题
 * c[i]：第i件物品的体积
 * w[i]：第i件物品的价值
 * f[i][v]：前i件物品装在v的背包里能够获得的最大价值
 * 状态转移方程：
 * f[i][v] = max{ f[i-1][v - k*c[i]] + k*w[i] | 0<= k*c[i] <= v }
 * 思路1：
 * 转化为01背包问题，即将每一件物品转化为 (k*c[i], k*w[i]) ，
 * 优化：二进制思想，将每一件物品转化为 (c[i]*2^k, w[i]*2^k), c[i]*2^k <= V
 * 思路2：
 * O(VN)的复杂度
 * 状态转移方程：
 * f[i][v] = max(f[i-1][v], f[i][v-c[i]] + w[i])
 * 伪代码：
 * for i = 1 .. N
 *   for v = 0 .. V
 *     f[v] = max(f[v], f[v-c[i]] + w[i])
 */

int completePack() {
  for (int i = 0; i < N; i++) {
    for (int j = c[i]; j <= V; j++) {
      f[j] = max(f[j], f[j-c[i]] + w[i]);
    }
  }
  return f[V];
}