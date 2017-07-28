#include <iostream>
using namespace std;

int n, m;
long long int map[52][52] = {0};
long long int mod = 1000000000000000000;
int dire[4][2] = {{1,-2}, {1, 2}, {2, -1}, {2, 1}};

bool legal(int x, int y) {
  return (x >= 1 && x <= n && y >= 1 && y <= m);
}

void deal1() {
  map[n][m] = 1;
  for (int i = n; i >= 1; i--) {
    for (int j = m; j >= 1; j--) {
      for (int k = 0; k < 4; k++) {
        if (legal(i+dire[k][0], j+dire[k][1])) {
          map[i][j] |= map[i+dire[k][0]][j+dire[k][1]];
        }
      }
    }
  }
  if (map[1][1] == 0) {
    cout << "NO" << endl;
  } else {
    cout << "(1,1)";
    int a = 1, b = 1;
    while (!(a == n && b == m)) {
      for (int k = 0; k < 4; k++) {
        if (legal(a+dire[k][0], b+dire[k][1])) {
          if (map[a+dire[k][0]][b+dire[k][1]] == 1) {
            a += dire[k][0];
            b += dire[k][1];
            break;
          }
        }
      }
      cout << "-(" << a << "," << b << ")";
    }
    cout << endl;
  }
}

void deal2(int x1, int y1, int x2, int y2) {
  map[x2][y2] = 1;
  for (int i = n; i >= 1; i--) {
    for (int j = m; j >= 1; j--) {
      for (int k = 0; k < 4; k++) {
        if (legal(i+dire[k][0], j+dire[k][1])) {
          map[i][j] = (map[i][j] + map[i+dire[k][0]][j+dire[k][1]]) % mod;
        }
      }
    }
  }
  cout << map[x1][y1] << endl;
}

int main() {
  int x1, y1, x2, y2;
  cin >> n >> m >> x1 >> y1 >> x2 >> y2;
  if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0) {
    deal1();
  } else {
    deal2(x1, y1, x2, y2);
  }
  return 0;
}