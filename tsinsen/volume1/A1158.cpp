#include <iostream>
using namespace std;

int pow(int a, int b) {
  int ans = 1;
  for (int i = 0; i < b; i++) {
    ans *= a;
  }
  return ans;
}

int main() {
  int ans = 0;
  int k, N, i = 0;
  cin >> k >> N;
  for (i = 0; i < 10; i++) {
    if ((1 << i) & N) {
      ans += pow(k, i);
    }
  }
  cout << ans << endl;
  return 0;
}