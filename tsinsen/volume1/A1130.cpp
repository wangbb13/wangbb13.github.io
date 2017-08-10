#include <iostream>
using namespace std;

int ans = 0;

void deal(int n) {
  ans++;
  for (int i = 1; i <= n/2; i++) {
    deal(i);
  }
}

int main() {
  int n;
  cin >> n;
  deal(n);
  cout << ans << endl;
  return 0;
}