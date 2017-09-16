#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
  int dp[503][503] = {0};
  int n, k;
  cin >> n >> k;
  int m = n - k + 1;
  int i, j;
  if (m == k) {
    cout << 1 << endl;
    return 0;
  }
  for (i = 0; i <= m; i++) {
    dp[i][0] = 1;
  }
  for (i = 1; i < m; i++) {
    for (j = 1; j <= i; j++) {
      dp[i][j] = (dp[i-1][j] + dp[i-1][j-1]) % 10007;
    }
  }
  for (j = 1; j <= k; j++) {
    dp[m][j] = (dp[m-1][j] + dp[m-1][j-1]) % 10007;
  }
  cout << dp[m][k] << endl;
  return 0;
}