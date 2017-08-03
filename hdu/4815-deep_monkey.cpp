#include <iostream>
#include <vector>
using namespace std;

vector<int> dp(40003, 0);

int main() {
  int T, N;
  int i, j, k;
  double P;
  cin >> T;
  while (T--) {
    cin >> N >> P;
    long long int base = 1 << N;
    dp[0] = 1;
    for (i = 0; i < N; i++) {
      cin >> k;
      for (j = 40000; j >= k; j--) {
        dp[j] += dp[j-k];
      }
    }
    j = 0;
    for (i = 0; i <= 40000; i++) {
      j += dp[i];
      if (((double)j / (double)base) - P > 1e-10) {
        cout << i << endl;
        break;
      }
    }
  }
}