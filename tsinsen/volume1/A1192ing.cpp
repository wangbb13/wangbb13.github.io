#include <iostream>
using namespace std;

// solving...

struct step {
  int x, y, d;
} res[5];

int g[7][5] = {0};
int f[7][5] = {0};

int N, sum = 0;

void move() {
  int i, j;
  for (i = 0; i < 5; i++) {
    for ()
  }
}

void deal(int i, int x, int y) {
  if (i == N) {
    if (legal()) {
      for (int j = 0; j < N; j++) {
        cout << res[j].x << " " << res[j].y << " " << res[j].d << endl;
      }
      exit(0);
    }
    return;
  }
  int j, k;
  for (k = y; k < 5; k++) {
    if (g[x][k] != 0) {

    }
  }
  for (j = x + 1; j < 7; j++) {
    for (k = 0; k < 5; k++) {
      if (g[x][k] != 0) {

      }
    }
  }
}

int main() {
  cin >> N;
  for (int i = 0; i < 5; i++) {
    int j, k = 0;
    while (true) {
      cin >> j;
      if (j == 0) {
        break;
      }
      sum++;
      g[k++][i] = j;
    }
  }
  deal(0, 0, 0);
  cout << -1 << endl;
  return 0;
}