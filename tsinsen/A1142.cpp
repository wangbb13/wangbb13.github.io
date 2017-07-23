#include <iostream>
#include <cstdio>
using namespace std;

int n, m;
int a[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
int b[8] = {-2, -1, 1, 2, -2, -1, 1, 2};

bool legal(int x, int y) {
  if (x >= 0 && x <= n && y >= 0 && y <= m) {
    return true;
  }
  return false;
}

int main() {
  long long int map[21][21] = {0};
  int x, y;
  int i, j;
  cin >> n >> m >> x >> y;
  map[x][y] = -1;
  for (i = 0; i < 8; i++) {
    if (legal(x+a[i], y+b[i])) {
      map[x+a[i]][y+b[i]] = -1;
    }
  }
  for (i = 0; i <= n; i++) {
    if (map[i][0] == -1) {
      for (j = i+1; j <= n; j++) {
        map[j][0] = -1;
      }
      break;
    } else {
      map[i][0] = 1;
    }
  }
  for (i = 0; i <= m; i++) {
    if (map[0][i] == -1) {
      for (j = i+1; j <= m; j++) {
        map[0][j] = -1;
      }
      break;
    } else {
      map[0][i] = 1;
    }
  }
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= m; j++) {
      if (map[i][j] != -1) {
        if (map[i-1][j] != -1) {
          map[i][j] += map[i-1][j];
        }
        if (map[i][j-1] != -1) {
          map[i][j] += map[i][j-1];
        }
      }
    }
  }
  cout << map[n][m] << endl;
  return 0;
}