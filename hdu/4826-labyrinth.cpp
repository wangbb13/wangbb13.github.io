#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
  int T, m, n;
  int i, j, k;
  vector< vector<int> > in(102, vector<int>(102, 0));
  cin >> T;
  k = 0;
  while (T--) {
    k++;
    cin >> m >> n;
    vector< vector<int> > dp(102, vector<int>(102, -1000000));
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) {
        cin >> in[i][j];
      }
    }
    dp[0][0] = in[0][0];
    for (i = 1; i < m; i++) {
      dp[i][0] = in[i][0] + dp[i-1][0];
    }
    for (j = 1; j < n; j++) {
      dp[0][j] = in[0][j] + dp[0][j-1];
      for (i = 1; i < m; i++) {
        dp[i][j] = max(dp[i][j-1], dp[i-1][j]) + in[i][j];
      }
      int mem = -1000000;
      for (i = m-1; i >= 0; i--) {
        mem = max(mem, dp[i][j-1]) + in[i][j];
        dp[i][j] = max(dp[i][j], mem);
      }
    }
    cout << "Case #" << k << ":" << endl;
    cout << dp[0][n-1] << endl;
  }
}