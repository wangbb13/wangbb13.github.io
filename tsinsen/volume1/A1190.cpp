#include <iostream>
using namespace std;

struct j {
  int x1, y1, x2, y2;
} g[10002];

int main() {
  int n, tx, ty, i, j, k, r, ans = -1;
  cin >> n;
  for (i = 1; i <= n; i++) {
    cin >> g[i].x1 >> g[i].y1 >> k >> r;
    g[i].x2 = g[i].x1 + k;
    g[i].y2 = g[i].y1 + r;
  }
  cin >> tx >> ty;
  for (i = 1; i <= n; i++) {
    if (tx >= g[i].x1 && tx <= g[i].x2 && ty >= g[i].y1 && ty <= g[i].y2) {
      ans = i;
    }
  }
}