/*
ID: wangbb21
LANG: C++
TASK: concom
 */
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

ofstream fout("concom.out");
ifstream fin("concom.in");

double com[102][102];
int N;

void dfs(int p) {
  int sta[102] = {0};
  double val[102];
  sta[p] = 1;
  while (true) {
    bool flag = true;
    for (int i = 1; i <= 100; i++) {
      val[i] = 0.;
    }
    for (int i = 1; i <= 100; i++) {
      if (sta[i] == 1) {
        for (int j = 1; j <= 100; j++) {
          val[j] += com[i][j];
        }
      }
    }
    for (int i = 1; i <= 100; i++) {
      if (sta[i] == 0 && val[i] > 0.5) {
        sta[i] = 1;
        flag = false;
      }
    }
    if (flag) {
      break;
    }
  }
  for (int i = 1; i <= 100; i++) {
    if (i != p && sta[i] == 1) {
      fout << p << " " << i << endl;
    }
  }
}

int main() {
  int i, j, k, v;
  for (i = 1; i <= 100; i++) {
    for (j = 1; j <= 100; j++) {
      com[i][j] = 0.0;
    }
  }
  fin >> N;
  for (i = 0; i < N; i++) {
    fin >> j >> k >> v;
    com[j][k] = (double)v / 100;
  }
  for (i = 1; i <= 100; i++) {
    dfs(i);
  }
  return 0;
}