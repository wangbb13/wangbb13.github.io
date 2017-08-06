#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int dp[1003] = {0};
  int cost[103], val[103];
  int T, M, i, j, k;
  cin >> T >> M;
  for (i = 0; i < M; i++) {
    cin >> cost[i] >> val[i];
  }
  for (i = 0; i < M; i++) {
    for (j = T; j >= cost[i]; j--) {
      dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
    }
  }
  cout << dp[T] << endl;
  return 0;
}