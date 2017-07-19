#include <iostream>
using namespace std;

int main() {
  int n, m;
  int i, j, k;
  int ans1 = 0, ans2 = 0;
  cin >> n >> m;
  if (n > m) {
    i = n;
    n = m;
    m = i;
  } // n <= m
  for (i = 1; i <= n; i++) {
    ans1 += (n - i + 1) * (m - i + 1);
  }
  for (i = 1; i <= n; i++) {
    for (j = 1; j < i; j++) {
      ans2 += (n - i + 1) * (m - j + 1);
    }
    for (j = i+1; j <= m; j++) {
      ans2 += (n - i + 1) * (m - j + 1);
    }
  }
  cout << ans1 << " " << ans2 << endl;
}