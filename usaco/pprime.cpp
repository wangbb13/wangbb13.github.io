/*
ID: wangbb21
LANG: C++
TASK: pprime
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

bool prime(int n) {
  if (n < 2) {
    return false;
  }
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int base[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
vector<int> pp;

void deal(int j, int k, int x) {
  if (j == k) {
    for (int i = 0; i < 10; i++) {
      pp.push_back(x+base[j]*i);
    }
    return;
  }
  if (j == k+1) {
    for (int i = 0; i < 10; i++) {
      pp.push_back(x + base[j]*i + base[k]*i);
    }
    return;
  }
  for (int i = 0; i < 10; i++) {
    deal(j-1, k+1, x + base[j]*i + base[k]*i);
  }
}

int main() {
  ofstream fout("pprime.out");
  ifstream fin("pprime.in");
  int a, b, i, j, k;
  fin >> a >> b;
  pp.push_back(5);
  pp.push_back(7);
  pp.push_back(11);
  for (i = 3; i < 9; i++) {
    j = i-1; k = 0;
    int x = base[j] * 1 + base[k] * 1;
    deal(j-1, k+1, x);
    x = base[j] * 3 + base[k] * 3;
    deal(j-1, k+1, x);
    x = base[j] * 7 + base[k] * 7;
    deal(j-1, k+1, x);
    x = base[j] * 9 + base[k] * 9;
    deal(j-1, k+1, x);
  }
  for (i = 0; i < pp.size(); i++) {
    if (pp[i] >= a && pp[i] <= b && prime(pp[i])) {
      fout << pp[i] << endl;
    }
  }
  return 0;
}
