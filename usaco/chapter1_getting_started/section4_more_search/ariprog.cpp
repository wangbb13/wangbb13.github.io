/*
ID: wangbb21
LANG: C++
TASK: ariprog
 */
#include <iostream>
#include <fstream>
using namespace std;

int map[125002] = {0};
int N, M;

int main() {
  ofstream fout("ariprog.out");
  ifstream fin("ariprog.in");
  fin >> N >> M;
  int i, j, k, mx, step;
  mx = M * M * 2;
  bool none = true;
  for (i = 0; i <= M; i++) {
    for (j = 0; j <= M; j++) {
      map[i*i + j*j] = 1;
    }
  }
  step = mx / (N - 1);
  for (j = 1; j <= step; j++) {
    int la = mx - (N - 1) * j;
    for (i = 0; i <= la; i++) {
      bool flag = true;
      int x = i;
      for (k = 0; k < N; k++) {
        if (map[x] == 0) {
          flag = false;
          break;
        }
        x += j;
      }
      if (flag) {
        none = false;
        fout << i << " " << j << endl;
      }
    }
  }
  if (none) {
    fout << "NONE" << endl;
  }
  return 0;
}
