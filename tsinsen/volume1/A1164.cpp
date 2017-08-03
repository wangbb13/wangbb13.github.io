#include <iostream>
using namespace std;

int main() {
  int m, n, k, l, d;
  int i, j;
  int x1, y1, x2, y2;
  // merge row, merge col
  // k for col, l for row
  int row[1003] = {0}, col[1003] = {0};
  cin >> m >> n >> k >> l >> d;
  for (i = 0; i < d; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    // row
    if (x1 == x2) {
      row[y1] += 1;
      row[y2] += 1;
    }
    // col
    if (y1 == y2) {
      col[x1] += 1;
      col[x2] += 1;
    }
  }
  for (i = 1; i < n; i++) {
    row[i] -= row[i-1];
  }
  for (i = 1; i < m; i++) {
    col[i] -= col[i-1];
  }
  int blank[1003] = {0};
  for (i = 0; i < k; i++) {
    int max = -1, p = 0;
    for (j = 1; j < m; j++) {
      if (col[j] > max && blank[j] == 0) {
        max = col[j];
        p = j;
      }
    }
    blank[p] = 1;
  }
  for (i = 1; i < m; i++) {
    if (blank[i]) {
      cout << i << " ";
    }
  }
  cout << endl;
  for (i = 0; i < n; i++) {
    blank[i] = 0;
  }
  for (i = 0; i < l; i++) {
    int max = -1, p = 0;
    for (j = 1; j < n; j++) {
      if (row[j] > max && blank[j] == 0) {
        max = row[j];
        p = j;
      }
    }
    blank[p] = 1;
  }
  for (i = 0; i < n; i++) {
    if (blank[i]) {
      cout << i << " ";
    }
  }
  cout << endl;
  return 0;
}
