#include <iostream>
#include <cmath>
using namespace std;

int score[352] = {0};
int steps[5] = {0};
int dp[42][42][42][42];
int N, M;

int main() {
  int i, j, k, r, s, t;
  cin >> N >> M;
  for (i = 1; i <= N; i++) {
    cin >> score[i];
  }
  for (i = 0; i < M; i++) {
    cin >> j;
    steps[j]++;
  }
  for (i = 0; i <= steps[1]; i++) {
    for (j = 0; j <= steps[2]; j++) {
      for (k = 0; k <= steps[3]; k++) {
        for (r = 0; r <= steps[4]; r++) {
          int& t = dp[i][j][k][r];
          t = 0;
          s = i + j * 2 + k * 3 + r * 4 + 1;
          if (i > 0) t = max(t, dp[i-1][j][k][r] + score[s]);
          if (j > 0) t = max(t, dp[i][j-1][k][r] + score[s]);
          if (k > 0) t = max(t, dp[i][j][k-1][r] + score[s]);
          if (r > 0) t = max(t, dp[i][j][k][r-1] + score[s]);
        }
      }
    }
  }
  cout << dp[steps[1]][steps[2]][steps[3]][steps[4]] + score[1] << endl;
  return 0;
}