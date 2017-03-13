#include <iostream>
#include <cmath>
using namespace std;

// 理解错了。。

int main(int argc, char const *argv[])
{
  double t, c, n1, n2;
  cin >> t;
  while (t--) {
    cin >> c;
    n1 = (int)((-1 + sqrt(1 + 8 * c)) / 2);
    n2 = n1 * (n1 + 1) / 2;
    if (n2 == c) {
      cout << n1 << endl;
    } else {
      cout << (c - n2) << endl;
    }
  }
  system("pause");
  return 0;
}