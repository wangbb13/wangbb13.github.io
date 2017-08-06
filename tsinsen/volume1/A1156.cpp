#include <iostream>
#include <cmath>
using namespace std;

int dp[30003] = {0};
int cost[25], val[25];

int main() {
  int N, m;
  int i, j, k;
  cin >> N >> m;
  for (i = 0; i < m; i++) {
    cin >> cost[i] >> val[i];
  }
  for (i = 0; i < m; i++) {
    for (j = N; j >= cost[i]; j--) {
      dp[j] = max(dp[j], dp[j - cost[i]] + cost[i] * val[i]);
    }
  }
  cout << dp[N] << endl;
  return 0;
}