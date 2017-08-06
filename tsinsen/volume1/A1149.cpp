#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string dp[11][1025];

string post_order(int i, int j) {
  if (i == j) {
    return dp[0][i];
  }
  int l = j - i + 1;
  int le = 0;
  while ((l & (1 << le)) == 0) { le++; }
  int m = (i + j) / 2;
  return post_order(i, m) + post_order(m+1, j) + dp[le][i];
}

int main() {
  int n, nn, i, j, k;
  char ch;
  cin >> n;
  nn = n;
  n = pow(2., n);
  for (i = 0; i < n; i++) {
    cin >> ch;
    if (ch == '0') {
      dp[0][i] = "B";
    } else {
      dp[0][i] = "I";
    }
  }
  j = 1;
  for (i = 1; i <= nn; i++) {
    for (k = 0; k < n; k += (2 * j)) {
      if (dp[i-1][k] == dp[i-1][k+j]) {
        dp[i][k] = dp[i-1][k];
      } else {
        dp[i][k] = "F";
      }
    }
    j *= 2;
  }
  cout << post_order(0, n-1) << endl;
  return 0;
}