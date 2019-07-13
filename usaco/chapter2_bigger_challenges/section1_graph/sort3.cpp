/*
ID: wangbb21
LANG: C++
TASK: sort3
 */
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int p[1002];

int main() {
  ofstream fout("sort3.out");
  ifstream fin("sort3.in");
  int N, n1, n12, n13, n2, n21, n23, n3, n31, n32, i, j, ans;
  n1 = n12 = n13 = n2 = n21 = n23 = n3 = n31 = n32 = 0;
  fin >> N;
  for (i = 0; i < N; i++) {
    fin >> j;
    if (j == 1) {
      n1++;
    } else if (j == 2) {
      n2++;
    } else {
      n3++;
    }
    p[i] = j;
  }
  for (i = 0; i < n1; i++) {
    if (p[i] == 2) {
      n12++;
    } else if (p[i] == 3) {
      n13++;
    }
  }
  for (j = 0; j < n2; j++, i++) {
    if (p[i] == 1) {
      n21++;
    } else if (p[i] == 3) {
      n23++;
    }
  }
  for (j = 0; j < n3; j++, i++) {
    if (p[i] == 1) {
      n31++;
    } else if (p[i] == 2) {
      n32++;
    }
  }
  i = min(n12, n21) + min(n13, n31);
  j = n21 + n31 - i;
  ans = i + j + max(n23, n32);  // n23和n32不相等，取最大值
  fout << ans << endl;
  return 0;
}