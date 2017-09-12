/*
ID: wangbb21
LANG: C++
TASK: ttwo
 */
#include <iostream>
#include <fstream>
using namespace std;

struct pair {
  int x, y;   // x row, y col
} F, C;

int dire[4][2] = {
  {-1, 0}, {0, 1}, {1, 0}, {0, -1}  // 北、东、南、西
};

int map[10][10] = {0};
int FD = 0, CD = 0;

bool legal(int x, int y) {
  if (x >= 0 && x < 10 && y >= 0 && y < 10 && (map[x][y] == 0)) {
    return true;
  }
  return false;
}

int main() {
  ofstream fout("ttwo.out");
  ifstream fin("ttwo.in");
  int i, j, ans = 0;
  char ch;
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      fin >> ch;
      if (ch == '*') {
        map[i][j] = 1;
      } else if (ch == 'F') {
        F.x = i;
        F.y = j;
      } else if (ch == 'C') {
        C.x = i;
        C.y = j;
      }
    }
  }
  while (ans < 10000) {
    ans ++;
    i = F.x + dire[FD][0];
    j = F.y + dire[FD][1];
    if (legal(i, j)) {
      F.x = i;
      F.y = j;
    } else {
      FD = (FD + 1) % 4;
    }

    i = C.x + dire[CD][0];
    j = C.y + dire[CD][1];
    if (legal(i, j)) {
      C.x = i;
      C.y = j;
    } else {
      CD = (CD + 1) % 4;
    }

    if (C.x == F.x && C.y == F.y) {
      fout << ans << endl;
      return 0;
    }
  }
  fout << 0 << endl;
  return 0;
}
