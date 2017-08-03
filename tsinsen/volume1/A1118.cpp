#include <iostream>
using namespace std;

// a < b
bool lesss(int a, int b) {
  long long int x, y;
  int ia = 1, ib = 1;
  int ca = a, cb = b;
  do {
    ia *= 10;
    a /= 10;
  } while (a > 0);
  do {
    ib *= 10;
    b /= 10;
  } while (b > 0);
  x = ca * ib + cb;
  y = cb * ia + ca;
  return (x > y);
}

int main() {
  int in[21] = {0};
  int n;
  int i, j, k;
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> in[i];
  }
  for (i = 0; i < n-1; i++) {
    for (j = n-1; j > i; j--) {
      if (lesss(in[j], in[j-1])) {
        k = in[j];
        in[j] = in[j-1];
        in[j-1] = k;
      }
    }
  }
  for (i = 0; i < n; i++) {
    cout << in[i];
  }
  cout << endl;
  return 0;
}