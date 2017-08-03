#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int n, m, p;
  int i, j, k;
  int cost[42], tm[42];
  int dp[42][42], in[42][42];
  int va[42][42][42];
  cin >> n >> m >> p;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      cin >> in[i][j];
    }
  }
  for (i = 0; i < n; i++) {
    cin >> cost[i];
  }
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      va[i][j][0] = in[i][j] - cost[i];
      for (k = 1; k < min(m-j, p); k++) {
        va[i][j][k] = va[i][j][k-1] + in[(i+k)%n][j+k];
      }
    }
  }
  for (j = 0; j < n; j++) {
    dp[0][j] = va[(j-1+n)%n][0][0];
    tm[1] = max(tm[1], dp[0][j]);
  }
  for (i = 1; i < m; i++) {
    tm[i+1] = tm[i];
    for (j = 0; j < n; j++) {
      dp[i][j] = -2147483647;
      for (k = 0; k < min(i+1, p); k++) {
        dp[i][j] = max(dp[i][j], tm[i-k]+va[(j-k+n)%n][i-k][k]);
      }
      tm[i+1] = max(tm[i+1], dp[i][j]);
    }
  }
  cout << tm[m] << endl;
  return 0;
}