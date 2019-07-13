/*
ID: wangbb21
LANG: C++
TASK: runround
 */
#include <iostream>
#include <fstream>
using namespace std;

bool run(unsigned long n) {
  int ary[20], sta[20] = {0};
  int flag[10] = {0};
  int p = 20;
  do {
    ary[--p] = n % 10;
    if (ary[p] == 0) {
      return false;
    }
    if (flag[ary[p]] == 1) {
      return false;
    } else {
      flag[ary[p]] = 1;
    }
    n /= 10;
  } while (n > 0);
  int idx = p, num, i, len = 20 - p;
  for (i = p; i < 20; i++) {
    num = ary[idx];
    idx = ((idx - p + num) % len) + p; // 15 16 17 18 19
    if (sta[idx] == 1) {
      return false;
    } else {
      sta[idx] = 1;
    }
  }
  return (idx == p);
}

int main() {
  ofstream fout("runround.out");
  ifstream fin("runround.in");
  int n;
  fin >> n;
  for (unsigned long i = n + 1; ; i++) {
    if (run(i)) {
      fout << i << endl;
      break;
    }
  }
  return 0;
}
