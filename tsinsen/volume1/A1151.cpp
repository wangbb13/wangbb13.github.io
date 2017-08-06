#include <iostream>
using namespace std;

int main() {
  int al[10];
  int i, j, ans = 0;
  for (i = 0; i < 10; i++) {
    cin >> al[i];
  }
  cin >> j;
  j += 30;
  for (i = 0; i < 10; i++) {
    if (j >= al[i]) {
      ans++;
    }
  }
  cout << ans << endl;
  return 0;
}