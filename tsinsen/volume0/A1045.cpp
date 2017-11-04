#include <iostream>
using namespace std;

int series[10005];

int main() {
  int t, n, m, i, j, x, y;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (i = 0; i < n; i++) {
      cin >> series[i];
    }
    for (i = 0; i < m; i++) {
      cin >> x >> y;
      x--; y--;
      j = series[x];
      series[x] = series[y];
      series[y] = j;
    }
    for (i = 0; i < n; i++) {
      cout << series[i] << endl;
    }
  }
  return 0;
}