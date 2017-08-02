#include <iostream>
#include <stack>
using namespace std;

int main() {
  int i, j, n;
  int dp[20][20];
  cin >> n;
  for (i = 1; i <= n; i++) {
    dp[i][0] = 1;
  }
  for (j = 1; j <= n; j++) {
    dp[0][j] = dp[1][j-1];
    for (i = 1; i <= n-j; i++) {
      dp[i][j] = dp[i-1][j] + dp[i+1][j-1];
    }
  }
  cout << dp[0][n] << endl;
  return 0;
}