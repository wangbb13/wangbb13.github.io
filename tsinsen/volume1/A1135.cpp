#include <iostream>
#include <cmath>
using namespace std;

int dp[202][10] = {0};
int n, k;

// 找准子问题
int main() {
  cin >> n >> k;
  int i, j, r;
  dp[0][1] = 1;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= min(i, k); j++) {
      for (r = 1; r <= j; r++) {
        dp[i][j] += dp[i-j][r];
      }
    }
  }
  cout << dp[n][k] << endl;
  return 0;
}