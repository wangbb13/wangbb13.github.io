#include <iostream>
using namespace std;

int main() {
  int m, s, t;
  cin >> m >> s >> t;
  int a = 0, b = 0, i;
  for (i = 1; i <= t; i++) {
    a += 17;
    if (m >= 10) {
      m -= 10;
      b += 60;
    } else {
      m += 4;
    }
    if (b > a) {
      a = b;
    }
    if (a >= s) {
      cout << "Yes" << endl;
      cout << i << endl;
      return 0;
    }
  }
  cout << "No" << endl;
  cout << a << endl;
  return 0;
}