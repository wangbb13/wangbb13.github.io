#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
  int T, N;
  int i, j, k;
  double P;
  cin >> T;
  while (T--) {
    cin >> N >> P;
    double all = pow(2., N);
    double thr = all * P;
    vector<long long int> dp(40003, 0);
    dp[0] = 1;
    for (i = 0; i < N; i++) {
      cin >> k;
      for (j = 40000; j >= k; j--) {
        dp[j] += dp[j-k];
      }
    }
    double sum = 0.;
    for (i = 0; i <= 40000; i++) {
      sum += dp[i];
      if (sum >= thr) {
        cout << i << endl;
        break;
      }
    }
  }
}