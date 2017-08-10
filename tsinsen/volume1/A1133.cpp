#include <iostream>
#include <cmath>
using namespace std;

int dp[20003] = {0};
int w[32] = {0};
int V, n;

int main() {
  int i, j;
  cin >> V >> n;
  for (i = 0; i < n; i++) {
    cin >> w[i];
  }
  for (i = 0; i < n; i++) {
    for (j = V; j >= w[i]; j--) {
      dp[j] = max(dp[j], dp[j-w[i]] + w[i]);
    }
  }
  cout << (V - dp[V]) << endl;
  return 0;
}

/*
24
6
8
3
12
7
9
7
*/