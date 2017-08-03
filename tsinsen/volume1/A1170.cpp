#include <iostream>
using namespace std;

int main() {
  int n, i, j, k;
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> j;
    if (j == 0) {
      continue;
    } else if (j == 1) {
      if (i != 0) {
        cout << "+";
      }
    } else if (j > 1) {
      if (i != 0) {
        cout << "+";
      }
      cout << j;
    } else if (j == -1) {
      cout << "-";
    } else {
      cout << j;
    }
    if (n - i != 1) {
      cout << "x^" << n-i;
    } else {
      cout << "x";
    }
  }
  cin >> j;
  if (j > 0) {
    cout << "+" << j;
  } else if (j < 0) {
    cout << j;
  }
  cout << endl;
  return 0;
}