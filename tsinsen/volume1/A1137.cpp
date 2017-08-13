#include <iostream>
#include <string>
using namespace std;

int dp[202][42] = {0};
int w[202][202] = {0};
int d[202] = {0};

int main() {
  int P, K, S, i, j, k, n;
  string str, ipt = " ";
  string dic[6];
  cin >> P >> K;
  for (i = 0; i < P; i++) {
    cin >> str;
    ipt = ipt + str;
  }
  cin >> S;
  for (i = 0; i < S; i++) {
    cin >> dic[i];
  }
  n = ipt.size() - 1;
  for (i = 1; i <= n; i++) {
    for (j = 0; j < S; j++) {
      if (ipt.substr(i, dic[j].size()) == dic[j] && (d[i] == 0 || d[i] > dic[j].size())) {
        d[i] = dic[j].size();
      }
    }
  }
  for (i = 1; i <= n; i++) {
    for (j = i; j <= n; j++) {
      w[i][j] = w[i][j-1];
      for (k = i; k <= j; k++) {
        w[i][j] += (d[k] == j - k + 1);
      }
    }
  }
  for (i = 1; i <= n; i++) {
    for (k = 1; k <= (i, K); k++) {
      for (j = k-1; j < i; j++) {
        dp[i][k] = max(dp[i][k], dp[j][k-1] + w[j+1][i]);
      }
    }
  }
  cout << dp[n][K] << endl;
  return 0;
}