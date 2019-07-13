/*
ID: wangbb21
LANG: C++
TASK: frac1
 */
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

int gcd(int a, int b) {
  while (b) {
    int c = a % b;
    a = b;
    b = c;
  }
  return a;
}

struct stc {
  double v;
  int i, j;
  bool operator < (const stc& x) const {
    return v < x.v;
  }
};

int main() {
  ofstream fout("frac1.out");
  ifstream fin("frac1.in");
  int N, i, j;
  double v;
  fin >> N;
  priority_queue< stc > pQ;
  for (i = 2; i <= N; i++) {
    for (j = 1; j < i; j++) {
      if (gcd(j, i) == 1) {
        stc e = {-(double)j / (double)i, j, i};
        pQ.push(e);
      }
    }
  }
  fout << "0/1" << endl;
  while (!pQ.empty()) {
    fout << pQ.top().i << "/" << pQ.top().j << endl;
    pQ.pop();
  }
  fout << "1/1" << endl;
  return 0;
}