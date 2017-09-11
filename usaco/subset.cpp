/*
ID: wangbb21
LANG: C++
TASK: subset
 */
#include <iostream>
#include <fstream>
using namespace std;

long long dp[400] = {0};
int N, S;

int main() {
  ofstream fout("subset.out");
  ifstream fin("subset.in");
  fin >> N;
  S = N * (N + 1) / 2;
  if (S % 2 == 1) {
    fout << 0 << endl;
    return 0;
  }
  S /= 2;
  dp[0] = 1;
  for (int i = 1; i <= N; i++) {
    for (int j = S; j >= i; j--) {
      dp[j] += dp[j - i];
    }
  }
  fout << dp[S] / 2 << endl;
  return 0;
}
