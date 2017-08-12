/*
ID: wangbb21
LANG: C++
TASK: numtri
 */
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int dp[1000][1000] = {0};
int ip[1000][1000] = {0};
int R;

int main() {
  ofstream fout("numtri.out");
  ifstream fin("numtri.in");
  int i, j, ans;
  fin >> R;
  for (i = 0; i < R; i++) {
    for (j = 0; j <= i; j++) {
      fin >> ip[i][j];
    }
  }
  dp[0][0] = ip[0][0];
  for (i = 1; i < R; i++) {
    dp[i][0] = ip[i][0] + dp[i-1][0];
    for (j = 0; j < i; j++) {
      dp[i][j] = ip[i][j] + max(dp[i-1][j], dp[i-1][j-1]);
    }
    dp[i][i] = ip[i][i] + dp[i-1][i-1];
  }
  ans = dp[R-1][0];
  for (i = 0; i < R; i++) {
    ans = max(ans, dp[R-1][i]);
  }
  fout << ans << endl;
  return 0;
}
