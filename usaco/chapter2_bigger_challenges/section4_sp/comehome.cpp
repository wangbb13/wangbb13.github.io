/*
ID: wangbb21
LANG: C++
TASK: comehome
 */
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

const int inf = 0x5fffffff;

int map[60][60] = {0};
int dist[60] = {0};
int flag[60] = {0};

int main() {
  ofstream fout("comehome.out");
  ifstream fin("comehome.in");
  int i, j, k, r, P;
  char s, t;
  for (i = 1; i <= 52; i++) {
    for (j = 1; j <= 52; j++) {
      map[i][j] = inf;
    }
    map[i][i] = 0;
  }
  fin >> P;
  for (i = 0; i < P; i++) {
    fin >> s >> t >> k;
    if (s < 'a') {
      r = 27 + (s - 'A');
    } else {
      r = s - 'a' + 1;
    }
    if (t < 'a') {
      j = 27 + (t - 'A');
    } else {
      j = t - 'a' + 1;
    }
    map[r][j] = min(map[r][j], k);
    map[j][r] = map[r][j];
  }
  for (i = 1; i <= 52; i++) {
    dist[i] = map[52][i];
  }
  flag[52] = 1;
  for (i = 0; i < 51; i++) {
    k = inf;
    r = -1;
    for (j = 1; j <= 52; j++) {
      if (flag[j] == 0 && dist[j] < k) {
        k = dist[j];
        r = j;
      }
    }
    if (k == inf) {
      break;
    }
    flag[r] = 1;
    for (j = 1; j <= 52; j++) {
      if (flag[j] == 0 && (k + map[r][j] < dist[j])) {
        dist[j] = k + map[r][j];
      }
    }
  }
  k = inf;
  r = 0;
  for (i = 27; i < 52; i++) {
    if (dist[i] < k) {
      k = dist[i];
      r = i;
    }
  }
  fout << (char)('A' + r - 27) << " " << k << endl;
  return 0;
}
