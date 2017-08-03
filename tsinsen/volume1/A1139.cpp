#include <iostream>
using namespace std;

int main() {
  double sum = 0., n = 0.;
  int k;
  cin >> k;
  while ((sum - k) < 1e-10) {
    n++;
    sum += 1 / n;
  }
  cout << (int)n << endl;
  return 0;
}