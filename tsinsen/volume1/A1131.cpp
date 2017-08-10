#include <iostream>
using namespace std;

int gcd(int a, int b) {
  while (b) {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}

int main() {
  int a, b, c, ans = 0;
  cin >> a >> b;
  if (b % a != 0) {
    cout << 0 << endl;
    return 0;
  }
  c = b / a;
  for (int i = 1; i <= c; i++) {
    if (c % i == 0 && gcd(i, c/i) == 1) {
      ans++;
    }
  }
  cout << ans << endl;
  return 0;
}