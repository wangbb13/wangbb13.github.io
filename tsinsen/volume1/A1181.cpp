#include <iostream>
using namespace std;

int ipt[502][502] = {0};

int main() {
  int n, i, j, k, a, b, ans = 0;
  cin >> n;
  for (i = 0; i < n; i++) {
    for (j = i+1; j < n; j++) {
      cin >> ipt[i][j];
      ipt[j][i] = ipt[i][j];
    }
  }
  for (i = 0; i < n; i++) {
    a = b = 0;
    for (j = 0; j < n; j++) {
      if (ipt[i][j] > a) {
        b = a;
        a = ipt[i][j];
      } else if (ipt[i][j] > b) {
        b = ipt[i][j];
      }
    }
    if (b > ans) { ans = b; }
  }
  cout << 1 << endl << ans << endl;
  return 0;
}