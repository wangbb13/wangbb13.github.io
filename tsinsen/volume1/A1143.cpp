#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int main() {
  int a[2][10000] = {0};
  int b[2][10000] = {0};
  int ai = 0, bi = 0;
  int wa = 0, la = 0, wb = 0, lb = 0;
  char in[20];
  int i, j, k;
  bool pro = true;
  while (pro) {
    cin >> in;
    k = strlen(in);
    for (i = 0; i < k; i++) {
      if (in[i] == 'E') {
        pro = false;
        // if (wa + la != 0) {
          a[0][ai] = wa;
          a[1][ai++] = la;
        // }
        // if (wb + lb != 0) {
          b[0][bi] = wb;
          b[1][bi++] = lb;
        // }
        break;
      }
      if (in[i] == 'W') {
        wa++;
        wb++;
      } else {
        la++;
        lb++;
      }
      if (abs(wa-la) >= 2 && (wa >= 11 || la >= 11)) {
        a[0][ai] = wa;
        a[1][ai++] = la;
        wa = 0;
        la = 0;
      }
      if (abs(wb-lb) >= 2 && (wb >= 21 || lb >= 21)) {
        b[0][bi] = wb;
        b[1][bi++] = lb;
        wb = 0;
        lb = 0;
      }
    }
  }
  for (i = 0; i < ai; i++) {
    cout << a[0][i] << ":" << a[1][i] << endl;
  }
  cout << endl;
  for (i = 0; i < bi; i++) {
    cout << b[0][i] << ":" << b[1][i] << endl;
  }
  return 0;
}