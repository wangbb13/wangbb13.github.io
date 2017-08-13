#include <iostream>
#include <cmath>
using namespace std;

long long int dp[42][8];
int N, K;
int ipt[42];

long long int calc(int i, int j) {
  long long int ans = 0;
  for (int x = i; x <= j; x++) {
    ans = ans * 10 + ipt[x];
  }
  return ans;
}

int main() {
  char ch;
  int i, j, k;
  cin >> N >> K;
  for (i = 0; i < N; i++) {
    cin >> ch;
    ipt[i+1] = ch - '0';
  }
  for (i = 1; i <= N; i++) {
    dp[i][0] = calc(1, i);
    for (k = 1; k <= min(i-1, K); k++) {
      for (j = k; j < i; j++) {
        dp[i][k] = max(dp[i][k], dp[j][k-1] * calc(j+1, i));
      }
    }
  }
  cout << dp[N][K] << endl;
  return 0;
}