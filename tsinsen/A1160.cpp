#include <iostream>
#include <cmath>
using namespace std;

int li[203] = {0};

int main() {
  int w, n, g;
  int i, j, k;
  int ans = 0;
  cin >> w >> n;
  for (i = 0; i < n; i++) {
    cin >> g;
    if (g > w - 5) {
      ans++;
    } else {
      li[g]++;
    }
  }
  for (i = w; i > w/2; i--) {
    if (li[i] > 0) {
      for (j = w-i; j >= 5; j--) {
        if (li[j] > 0) {
          k = min(li[i], li[j]);
          ans += k;
          li[i] -= k;
          li[j] -= k;
          if (li[i] == 0) {
            break;
          }
        }
      }
      if (li[i] > 0) {
        ans += li[i];
      }
    }
  }
  k = 0;
  for (i = w / 2; i >= 5; i--) {
    k += li[i];
  }
  ans += (k / 2 + (k % 2 != 0));
  cout << ans << endl;
  return 0;
}