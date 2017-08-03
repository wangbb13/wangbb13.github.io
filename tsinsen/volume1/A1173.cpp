#include <iostream>
#include <cmath>
using namespace std;

int in[1003][1003];
int cost[1003], mv[1003] = {0};
int n, m, p;

int main() {
  cin >> n >> m >> p;
  int i, j, k;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= m; j++) {
      cin >> in[i][j];
    }
  }
  for (i = 1; i <= n; i++) {
    cin >> cost[i];
  }
  for (i = 1; i <= m; i++) {
    for (j = 1; j <=n; j++) {
      int r = j-1, val = 0;
      if (r == 0) {
        r = n;
      }
      val += in[r][i];
      for (k = 1; k <= p; k++) {
        if (i - k < 0) {
          continue;
        }
        mv[i] = max(mv[i], mv[i-k] + val - cost[r]);
        r--;
        if (r == 0) {
          r = n;
        }
        val += in[r][i-k];
      }
    }
  }
  cout << mv[m] << endl;
  return 0;
}