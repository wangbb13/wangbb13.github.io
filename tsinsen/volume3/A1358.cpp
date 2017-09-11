#include <iostream>
#include <cmath>
using namespace std;

int N, M;
int mat[102][102] = {0};
int tmp[102][102] = {0};

int main() {
  int i, j, k, mx = 0, ans = 0;
  cin >> N >> M;
  for (i = 1; i <= M; i++) {
    cin >> mat[1][i];
    tmp[1][i] = mat[1][i];
  }
  for (i = 2; i < N; i++) {
    cin >> mat[i][1];
    tmp[i][1] = mat[i][1];
    for (j = 2; j < M; j++) {
      cin >> mat[i][j];
      // tmp[i][j] = mat[i][j];
      mx = max(mx, mat[i][j]);
    }
    cin >> mat[i][M];
    tmp[i][M] = mat[i][M];
  }
  for (i = 1; i <= M; i++) {
    cin >> mat[N][i];
    tmp[N][i] = mat[N][i];
  }
  for (i = 2; i < N; i++) {
    for (j = 2; j < M; j++) {
      tmp[i][j] = mx;
    }
  }
  while (true) {
    bool flag = true;
    // key
    for (i = 2; i < N; i++) {
      for (j = 2; j < M; j++) {
        if (tmp[i][j] > mat[i][j]) {
          int val = min(min(tmp[i-1][j], tmp[i+1][j]), min(tmp[i][j-1], tmp[i][j+1]));
          if (tmp[i][j] > val) {
            flag = false;
            tmp[i][j] = max(val, mat[i][j]);
          }
        }
      }
    }
    // end
    if (flag) {
      break;
    }
  }
  for (i = 2; i < N; i++) {
    for (j = 2; j < M; j++) {
      ans += (tmp[i][j] - mat[i][j]);
    }
  }
  cout << ans << endl;
  return 0;
}