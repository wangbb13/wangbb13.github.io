#include <iostream>
using namespace std;

int n, m;
int dp[33][33] = {0};

int main() {
  cin >> n >> m;
  int i, j;
  dp[0][1] = 1;
  for (i = 1; i <= m; i++) {
    dp[i][1] = dp[i-1][n] + dp[i-1][2];
    for (j = 2; j < n; j++) {
      dp[i][j] = dp[i-1][j-1] + dp[i-1][j+1];
    }
    dp[i][n] = dp[i-1][1] + dp[i-1][n-1];
  }
  cout << dp[m][1] << endl;
  return 0;
}