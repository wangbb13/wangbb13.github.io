/*
ID: wangbb21
LANG: C++
TASK: zerosum
 */
#include <iostream>
#include <fstream>
using namespace std;

ofstream fout("zerosum.out");
ifstream fin("zerosum.in");

char op[10];
int N;

void dfs(int p) {
  if (p == N) {
    int res = 1, i = 1, j = 2, a = 1, b;
    char ch;
    while (i < p && op[i] == ' ') {
      a = a * 10 + j;
      i++;
      j++;
    }
    if (i == p) {
      return;
    }
    while (i < p) {
      ch = op[i];
      b = j;
      i++;
      j++;
      while (i < p && op[i] == ' ') {
        b = b * 10 + j;
        i++;
        j++;
      }
      if (ch == '+') {
        res = a + b;
      } else {
        res = a - b;
      }
      a = res;
    }
    if (res == 0) {
      fout << 1;
      for (int i = 1; i < N; i++) {
        fout << op[i] << (i+1);
      }
      fout << endl;
    }
    return;
  }
  op[p] = ' ';
  dfs(p + 1);
  op[p] = '+';
  dfs(p + 1);
  op[p] = '-';
  dfs(p + 1);
}

int main() {
  fin >> N;
  dfs(1);
  return 0;
}
