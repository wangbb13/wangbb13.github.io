#include <iostream>
using namespace std;

void show(int n) {
  int i;
  if (n == 3) {
    cout << "2+2(0)";
    return;
  }
  if (n == 2) {
    cout << 2;
    return;
  }
  if (n == 1) {
    cout << "2(0)";
    return;
  }
  for (i = 31; i > 1; i--) {
    if (n & (1 << i)) {
      cout << 2 << "(";
      show(i);
      cout << ")";
      break;
    }
  }
  for (i--; i > 1; i--) {
    if (n & (1 << i)) {
      cout << "+" << 2 << "(";
      show(i);
      cout << ")";
    }
  }
  if (n & 2) {
    cout << "+" << 2;
  }
  if (n & 1) {
    cout << "+" << 2 << "(" << 0 << ")";
  }
}

int main() {
  int n;
  cin >> n;
  show(n);
  cout << endl;
  return 0;
}