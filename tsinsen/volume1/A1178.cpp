#include <iostream>
using namespace std;

int num(int n) {
  int ans = 0;
  do {
    if (n % 10 == 2) {
      ans++;
    }
    n /= 10;
  } while (n > 0);
  return ans;
}

int main() {
  int l, r, i, ans = 0;
  cin >> l >> r;
  for (i = l; i <= r; i++) {
    ans += num(i);
  }
  cout << ans << endl;
  return 0;
}