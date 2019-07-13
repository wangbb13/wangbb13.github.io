/*
ID: wangbb21
LANG: C++
TASK: sprime
 */
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

ofstream fout("sprime.out");
int base[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
int N;

bool prime(int n) {
  if (n < 2) { return false; }
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) { return false; }
  }
  return true;
}

void deal(int x, int n) {
  if (n == N) {
    fout << x << endl;
    return;
  }
  for (int i = 0; i < 10; i++) {
    int y = x*10 + i;
    if (prime(y)) {
      deal(y, n+1);
    }
  }
}

int main() {
  ifstream fin("sprime.in");
  fin >> N;
  deal(2, 1);
  deal(3, 1);
  deal(5, 1);
  deal(7, 1);
  return 0;
}
