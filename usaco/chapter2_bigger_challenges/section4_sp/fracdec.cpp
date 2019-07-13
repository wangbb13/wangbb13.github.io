/*
ID: wangbb21
LANG: C++
TASK: fracdec
 */
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int flag[1000002] = {0};

int size(int a) {
  int ans = 0;
  do {
    ans ++;
    a /= 10;
  } while (a > 0);
  return ans;
}

int main() {
  ofstream fout("fracdec.out");
  ifstream fin("fracdec.in");
  int i, j, N, D, sh, re, rtn;
  vector<int> g; // 余数，商
  fin >> N >> D;
  sh = N / D;
  re = N % D;
  if (re == 0) {
    fout << (N / D) << ".0" << endl;
    return 0;
  }
  j = D * 10;
  for (i = 0; i < j; i++) {
    flag[i] = -1;
  }
  i = 0;
  while (true) {
    rtn = flag[re];
    if (rtn >= 0) {
      break;
    }
    if (re == 0) {
      break;
    }
    flag[re] = i;
    re *= 10;
    g.push_back(re / D);
    re = re % D;
    i++;
  }
  fout << sh << ".";
  j = size(sh) + 1;
  if (rtn == -1) {
    for (i = 0; i < g.size(); i++) {
      fout << g[i];
      j++;
      if (j == 76) {
        fout << endl;
        j = 0;
      }
    }
    fout << endl;
  } else {
    for (i = 0; i < rtn; i++) {
      fout << g[i];
      j++;
      if (j == 76) {
        fout << endl;
        j = 0;
      }
    }
    fout << "(";
    j++;
    if (j == 76) {
      fout << endl;
      j = 0;
    }
    for (; i < g.size(); i++) {
      fout << g[i];
      j++;
      if (j == 76) {
        fout << endl;
        j = 0;
      }
    }
    fout << ")" << endl;
  }
  return 0;
}
