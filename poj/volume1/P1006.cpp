#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int p, e, i, d, j = 1, k;
  while((cin >> p >> e >> i >> d) && (p >= 0)) {
    p %= 23;
    e %= 28;
    i %= 33;
    k = max(max(p, e), i);
    while (!((k - p) % 23 == 0 && (k - e) % 28 == 0 && (k - i) % 33 == 0)) k++;
    printf("Case %d: the next triple peak occurs in %d days.\n", j++, (k - d) > 0 ? (k - d) : (k - d + 21252));
  }
  return 0;
}