#include <iostream>
using namespace std;

int m[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int num(int n) {
  int ans = 0;
  do {
    ans += m[n%10];
    n /= 10;
  } while (n > 0);
  return ans;
}

int main() {
  int ans[30] = {0};
  int a, n;
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      a = num(i) + num(j) + num(i+j) + 4;
      if (a <= 24) {
        ans[a]++;
      }
    }
  }
  cin >> n;
  cout << ans[n] << endl;
  return 0;
}
