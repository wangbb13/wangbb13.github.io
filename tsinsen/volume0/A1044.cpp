#include <iostream>
using namespace std;

int dp[21];

int main() {
  dp[1] = 1;
  dp[2] = 2;
  dp[3] = 4;
  int i;
  for (i = 4; i < 21; i++) {
    dp[i] = 2 * dp[i-1] - dp[i-3];
  }
  while (true) {
    cin >> i;
    if (i == 0) {
      break;
    }
    cout << dp[i] << endl;
  }
  return 0;
}