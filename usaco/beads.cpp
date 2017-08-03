/*
ID: wangbb21
LANG: C++
TASK: beads
 */
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int main() {
  ofstream fout("beads.out");
  ifstream fin("beads.in");
  int n, i, j, k, r, p, ans = 0;
  int in[400];
  char ch;
  bool one = false, two = false;
  fin >> n;
  for (i = 0; i < n; i++) {
    fin >> ch;
    if (ch == 'w') {
      in[i] = 0;
    } else if (ch == 'r') {
      in[i] = 1;
      one = true;
    } else {
      in[i] = 2;
      two = true;
    }
  }
  if (!(one && two)) {
    fout << n << endl;
    return 0;
  }
  for (i = 0; i < n; i++) {
    j = i-1;
    if (i == 0) { j = n-1; }
    if (in[i] != in[j]) {
      r = 0;
      if (in[i] > 0) {
        p = i;
        while (p < n && (in[p] == in[i] || in[p] == 0)) { p++; r++; }
        if (p == n) {
          p = 0;
          while (p < j && (in[p] == in[i] || in[p] == 0)) { p++; r++; }
        }
        p = j;
        while (p >= 0 && (in[p] == (3-in[i]) || in[p] == 0)) { p--; r++; }
        if (p < 0) {
          p = n-1;
          while (p > i && (in[p] == (3-in[i]) || in[p] == 0)) { p--; r++; }
        }
      } else if (in[j] > 0) {
        p = i;
        while (p < n && (in[p] == (3-in[j]) || in[p] == 0)) { p++; r++; }
        if (p == n) {
          p = 0;
          while (p < j && (in[p] == (3-in[j]) || in[p] == 0)) { p++; r++; }
        }
        p = j;
        while (p >= 0 && (in[p] == in[j] || in[p] == 0)) { p--; r++; }
        if (p < 0) {
          p = n-1;
          while (p > i && (in[p] == in[j] || in[p] == 0)) { p--; r++; }
        }
      }
      ans = max(ans, r);
    }
  }
  fout << min(ans,n) << endl;
  return 0;
}
