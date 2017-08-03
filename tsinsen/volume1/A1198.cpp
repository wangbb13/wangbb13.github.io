#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

double compute(vector<double> array, int n) {
  int k, i, j;
  vector< vector<double> > dp(n, vector<double>(n, 0));
  for (i = 0; i < n; i++) {
    dp[i][i] = array[i] * 2;
  }
  for (k = 1; k < n; k++) {
    for (i = 0; i < n-k; i++) {
      dp[i][i+k] = max((dp[i][i] + dp[i+1][i+k] * 2), (dp[i+k][i+k] + dp[i][i+k-1] * 2));
    }
  }
  return dp[0][n-1];
}

int main(int argc, char const *argv[])
{
  int n, m;
  int i, j, k, l;
  double ans;
  vector< vector<double> > input(80, vector<double>(80, 0));
  cin >> n >> m;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      cin >> input[i][j];
    }
  }
  ans = 0;
  for (i = 0; i < n; i++) {
    ans += compute(input[i], m);
  }
  cout << setprecision(0) << std::fixed << ans << endl;
  return 0;
}