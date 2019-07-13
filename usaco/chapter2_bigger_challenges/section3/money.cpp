/*
ID: wangbb21
LANG: C++
TASK: money
 */
#include <iostream>
#include <fstream>
using namespace std;

int V, N;
long long dp[10002] = {0};

int main() {
  ofstream fout("money.out");
  ifstream fin("money.in");
  fin >> V >> N;
  int i, j, coin;
  dp[0] = 1;
  for (i = 0; i < V; i++) {
    fin >> coin;
    for (j = coin; j <= N; j++) {
      dp[j] += dp[j - coin];
    }
  }
  fout << dp[N] << endl;
  return 0;
}
