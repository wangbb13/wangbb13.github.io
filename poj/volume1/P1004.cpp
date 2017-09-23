#include <iostream>
using namespace std;

int main() {
  double ans = 0., a;
  for (int i = 0; i < 12; i++) {
    cin >> a;
    ans += a;
  }
  cout << "$" << (ans / 12) << endl;
  return 0;
}