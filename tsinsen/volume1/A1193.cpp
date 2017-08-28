#include <iostream>
#include <cmath>
using namespace std;

// C_k_n = C_k-1_n-1 + C_k-1_n
// C_k_n * a^n * b^(k-n) = C_k-1_n-1 * a^n * b^(k-n) + C_k-1_n * a^n * b^(k-n)
// 
// a = b + c
// a % x = (b % x + c % x) % x
// a = b * c
// a % x = (b * (c % x)) % x
// 
// dp[i][j] = ((dp[i-1][j-1] * (a % x)) % x + (dp[i-1][j] * (b % x)) % x) % x
// i >= j
// 
// res: dp[k][n]

int dp[1001][1001] = {0};

int main() {
  int a, b, k, n, m, i, j, mod = 10007;
  cin >> a >> b >> k >> n >> m;
  if (k == 0) {
    cout << 1 << endl;
    return 0;
  }
  n = min(n, m);
  a %= mod;
  b %= mod;
  dp[0][0] = 1;
  for (i = 1; i <= k; i++) {
    dp[i][0] = (dp[i-1][0] * b) % mod;
    for (j = 1; j <= min(i, n); j++) {
      dp[i][j] = ( ((dp[i-1][j-1] * a) % mod) + ((dp[i-1][j] * b) % mod) ) % mod;
    }
  }
  cout << dp[k][n] << endl;
  return 0;
}