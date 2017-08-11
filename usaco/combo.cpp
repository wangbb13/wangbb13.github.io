/*
ID: wangbb21
LANG: C++
TASK: combo
 */
#include <iostream>
#include <fstream>
using namespace std;

int map[101][101][101] = {0};
int N, a, b, c, x, y, z;

// 注意细节
int main() {
  ofstream fout("combo.out");
  ifstream fin("combo.in");
  int ans = 0, i, j, k, r, s, t;
  fin >> N >> a >> b >> c >> x >> y >> z;
  for (i = a-2; i <= a+2; i++) {
    r = i;
    while (r < 1) { r += N; }
    while (r > N) { r -= N; }
    for (j = b-2; j <= b+2; j++) {
      s = j;
      while (s < 1) { s += N; }
      while (s > N) { s -= N; }
      for (k = c-2; k <= c+2; k++) {
        t = k;
        while (t < 1) { t += N; }
        while (t > N) { t -= N; }
        if (map[r][s][t] == 0) {
          map[r][s][t] = 1;
          ans++;
        }
      }
    }
  }
  for (i = x-2; i <= x+2; i++) {
    r = i;
    while (r < 1) { r += N; }
    while (r > N) { r -= N; }
    for (j = y-2; j <= y+2; j++) {
      s = j;
      while (s < 1) { s += N; }
      while (s > N) { s -= N; }
      for (k = z-2; k <= z+2; k++) {
        t = k;
        while (t < 1) { t += N; }
        while (t > N) { t -= N; }
        if (map[r][s][t] == 0) {
          map[r][s][t] = 1;
          ans++;
        }
      }
    }
  }
  fout << ans << endl;
  return 0;
}
