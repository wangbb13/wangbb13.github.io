#include <iostream>
using namespace std;

int al[1001] = {0};
int M;

int main() {
  int i, j, ans = 0;
  cin >> M;
  for (i = 0; i < M; i++) {
    cin >> j;
    al[j] = 1;
  }
  for (i = 0; i < 1001; i++) {
    ans += al[i];
  }
  cout << ans << endl;
  for (i = 0; i < 1001; i++) {
    if (al[i]) {
      cout << i << " ";
    }
  }
  cout << endl;
  return 0;
}