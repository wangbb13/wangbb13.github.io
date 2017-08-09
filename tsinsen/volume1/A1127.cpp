#include <iostream>
#include <cmath>
using namespace std;

int dp[11][11][11][11] = {0};
int mp[11][11] = {0};
int n;

int main() {
  int i, j, k, r, ans = 0;
  cin >> n;
  while (true) {
    cin >> i >> j >> k;
    if (i == 0 && j == 0 && k == 0) {
      break;
    }
    mp[i][j] = k;
  }
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      for (k = 1; k <= n; k++) {
        for (r = 1; r <= n; r++) {
          if (i == k && j == r) {
            continue;
          }
          dp[i][j][k][r] = max(max(dp[i-1][j][k-1][r], dp[i-1][j][k][r-1]), max(dp[i][j-1][k-1][r], dp[i][j-1][k][r-1])) + mp[i][j] + mp[k][r];
        }
      }
    }
  }
  cout << (mp[1][1] + mp[n][n] + dp[n][n-1][n-1][n]) << endl;
  return 0;
}

/*
8
2 3 13
2 6 6
3 5 7
4 4 14
5 2 21
5 6 4
6 3 15
7 2 14
0 0 0
*/