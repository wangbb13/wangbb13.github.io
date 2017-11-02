/*
 * fn = sigma (i = 1 to n) i
 * Input  : n1,  n2, ..
 * Output : fn1, fn2, ..
 */
#include <iostream>
using namespace std;

int main() {
  int n;
  while (cin >> n) {
    if (n % 2 == 0) {
      cout << (n / 2 * (n+1)) << endl << endl;
    } else {
      cout << ((n+1) / 2 * n) << endl << endl;
    }
  }
  return 0;
}