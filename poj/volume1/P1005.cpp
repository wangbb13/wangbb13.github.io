#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.1415926;

int main() {
  int n, year, i = 1;
  double x, y, s;
  cin >> n;
  while (n--) {
    cin >> x >> y;
    s = PI * (x * x + y * y) / 100;
    year = (int)s;
    printf("Property %d: This property will begin eroding in year %d.\n", i++, year + 1);
  }
  printf("END OF OUTPUT.\n");
  return 0;
}