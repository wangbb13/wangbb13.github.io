#include <iostream>
using namespace std;

int main() {
  int m = 0, p = 0, a, b, i;
  for (i = 0; i < 7; i++) {
    cin >> a >> b;
    if (a+b-8 > m) {
      m = a + b - 8;
      p = i + 1;
    }
  }
  cout << p << endl;
  return 0;
}