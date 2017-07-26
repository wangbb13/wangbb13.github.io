#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int m, n;
  int i, j, k, p;
  int a[51][51] = {0};
  int dp[51][51][51][51] = {0};
  cin >> m >> n;
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  if (m == 0 || n == 0) {
    cout << 0 << endl;
    return 0;
  }
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      for (k = 1; k <= m; k++) {
        for (p = 1; p <= n; p++) {
          if (i == k && j == p) {
            continue;
          }
          dp[i][j][k][p] = a[i][j] + a[k][p] + max(max(dp[i-1][j][k-1][p], dp[i-1][j][k][p-1]), max(dp[i][j-1][k-1][p], dp[i][j-1][k][p-1]));
        }
      }
    }
  }
  cout << dp[m][n-1][m-1][n] << endl;
  return 0;
}