/*
ID: wangbb21
LANG: C++
TASK: milk2
 */
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int al[1000001] = {0};

int main() {
  ofstream fout("milk2.out");
  ifstream fin("milk2.in");
  int n, i, j, a, b, fa, fi, ma = 0, mi = 0, end = -1, start = 1000001;
  fin >> n;
  for (i  = 0; i < n; i++) {
    fin >> a >> b;
    end = max(end, b);
    start = min(start, a);
    for (j = a; j < b; j++) {
      al[j] = 1;
    }
  }
  for (i = start; i < end; ) {
    if (al[i] == 0) {
      fi = 0;
      while (i < end && al[i] == 0) { i++; fi++; }
      mi = max(mi, fi);
    } else {
      fa = 0;
      while (i < end && al[i] == 1) { i++; fa++; }
      ma = max(ma, fa);
    }
  }
  fout << ma << " " << mi << endl;
  return 0;
}
