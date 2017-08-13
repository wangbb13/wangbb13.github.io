#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

double a, b, c, d;

bool same(double i, double j) {
  return ((i > 0 && j > 0) || (i < 0 && j < 0));
}

double func(double x) {
  double ans = a * pow(x, 3) + b * pow(x, 2) + c * x + d;
  return ans;
}

void deal(double l, double r) {
  double vall = func(l);
  double valr = func(r);
  double mid, valm;
  while ((r - l) > 1e-3) {
    mid = (l + r) / 2;
    valm = func(mid);
    if (same(vall, valm)) {
      l = mid;
      vall = valm;
    } else {
      r = mid;
      valr = valm;
    }
  }
  printf("%.2f ", r);
}

int main() {
  cin >> a >> b >> c >> d;
  double p1 = (-b - sqrt(b * b - 3 * a * c)) / (3 * a);
  double p2 = (-b + sqrt(b * b - 3 * a * c)) / (3 * a);
  deal(-101., p1);
  deal(p1, p2);
  deal(p2, 101.);
  return 0;
}