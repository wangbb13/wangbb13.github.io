#include <iostream>
#include <cmath>
using namespace std;

int dp[53][53][10];
int ip[53][53][10];
int va[53][53];
int in[53];
int n, m;

int mod(int n) {
  if (n > 0) {
    return n % 10;
  } else {
    return (10 - ((-n) % 10)) % 10;
  }
}

int main() {
  int i, j, k, r;
  cin >> n >> m;
  m--;
  for (i = 1; i <= n; i++) {
    cin >> in[i];
  }
  if (m == 0) {
    j = 0;
    for (i = 1; i <= n; i++) {
      j += in[i];
    }
    k = mod(j);
    cout << k << endl << k << endl;
    return 0;
  }
  for (i = 1; i <= n; i++) {
    int last = 0;
    for (j = 1; j < n; j++) {
      k = i + j - 1;
      if (k > n) { k -= n; }
      last += in[k];
      va[i][k] = mod(last);
    }
  }
  for (i = 1; i < n; i++) {
    for (j = 1; j <= n; j++) {
      int end = j + i - 1;
      if (end > n) { end -= n; }
      dp[j][end][1] = va[j][end];
      ip[j][end][1] = va[j][end];
      for (k = 2; k <= min(i, m); k++) {
        int mi = 2147483647, ma = -1, fa, fi, ke, kf;
        for (r = 1; r <= i-k+1; r++) {
          ke = j + r - 1;
          if (ke > n) { ke -= n; }
          kf = ke + 1;
          if (kf > n) { kf = 1; }
          fa = dp[j][ke][1] * dp[kf][end][k-1];
          fi = ip[j][ke][1] * ip[kf][end][k-1];
          ma = max(ma, fa);
          mi = min(mi, fi);
        }
        dp[j][end][k] = ma;
        ip[j][end][k] = mi;
      }
    }
  }
  int fa, fi, ma = -1, mi = 2147483647;
  for (i = 1; i <= n; i++) {
    int back = i - 1;
    if (back == 0) { back = n; }
    for (j = 1; j <= n-m; j++) {
      int end = i + j - 1;
      if (end > n) { end -= n; }
      int front = end + 1;
      if (front > n) { front = 1; }
      fa = dp[i][end][1] * dp[front][back][m];
      fi = ip[i][end][1] * ip[front][back][m];
      ma = max(ma, fa);
      mi = min(mi, fi);
    }
  }
  cout << mi << endl << ma << endl;
  return 0;
}