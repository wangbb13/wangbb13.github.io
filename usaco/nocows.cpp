/*
ID: wangbb21
LANG: C++
TASK: nocows
 */
#include <iostream>
#include <fstream>
using namespace std;

long long dp[202][102] = {0};
int N, K;

int main() {
  ofstream fout("nocows.out");
  ifstream fin("nocows.in");
  fin >> N >> K;
  int i, j, k;
  for (i = 1; i <= K; i++) {
    dp[1][i] = 1;
  }
  for (j = 2; j <= K; j++) {
    for (i = 1; i <= N; i++) {
      for (k = 1; k <= (i - 2); k++) {
        dp[i][j] += dp[k][j - 1] * dp[i - k - 1][j - 1];
        dp[i][j] %= 9901;
      }
    }
  }
  fout << (dp[N][K] - dp[N][K-1] + 9901) % 9901 << endl;
  return 0;
}