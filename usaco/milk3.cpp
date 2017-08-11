/*
ID: wangbb21
LANG: C++
TASK: milk3
 */
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int map[21][21][21] = {0};
int res[21] = {0};
int a, b, c;

void bfs(int level) {
  bool stop = true; int d;
  for (int i = 0; i <= a; i++) {
    for (int j = 0; j <= b; j++) {
      for (int k = 0; k <= c; k++) {
        if (map[i][j][k] == level) {
          if (i == 0) {
            res[k] = 1;
          }
          d = min(i, b-j);
          if (map[i-d][j+d][k] == 0) {
            map[i-d][j+d][k] = level + 1;
            stop = false;
          }
          d = min(i, c-k);
          if (map[i-d][j][k+d] == 0) {
            map[i-d][j][k+d] = level + 1;
            stop = false;
          }
          d = min(j, a-i);
          if (map[i+d][j-d][k] == 0) {
            map[i+d][j-d][k] = level + 1;
            stop = false;
          }
          d = min(j, c-k);
          if (map[i][j-d][k+d] == 0) {
            map[i][j-d][k+d] = level + 1;
            stop = false;
          }
          d = min(k, a-i);
          if (map[i+d][j][k-d] == 0) {
            map[i+d][j][k-d] = level + 1;
            stop = false;
          }
          d = min(k, b-j);
          if (map[i][j+d][k-d] == 0) {
            map[i][j+d][k-d] = level + 1;
            stop = false;
          }
        }
      }
    }
  }
  if (stop) {
    return;
  }
  bfs(level+1);
}

int main() {
  ofstream fout("milk3.out");
  ifstream fin("milk3.in");
  fin >> a >> b >> c;
  map[0][0][c] = 1;
  bfs(1);
  int i = 0;
  while (i <= c && res[i] == 0) { i++; }
  fout << i;
  for (i++; i <= c; i++) {
    if (res[i] == 1) {
      fout << " " << i;
    }
  }
  fout << endl;
  return 0;
}
