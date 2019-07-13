/*
ID: wangbb21
LANG: C++
TASK: castle
 */
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int ipt[51][51] = {0};
int uf[2501] = {0};
int uf_cnt[2501] = {0};
int N, M, cnt, mx_room;

void init(int x) {
  for (int i = 1; i <= x; i++) {
    uf[i] = i;
    uf_cnt[i] = 1;
  }
  cnt = x;
  mx_room = 1;
}

int find(int x) {
  return x == uf[x] ? x : uf[x] = find(uf[x]);
}

void merge(int x, int y) {
  int a = find(x), b = find(y);
  if (a != b) {
    uf[a] = b;
    uf_cnt[b] += uf_cnt[a];
    uf_cnt[a] = uf_cnt[b];
    cnt--;
    mx_room = max(mx_room, uf_cnt[b]);
  }
}

int main() {
  ofstream fout("castle.out");
  ifstream fin("castle.in");
  fin >> N >> M;  // n, column; m, row
  int i, j, k;
  for (i = 1; i <= M; i++) {
    for (j = 1; j <= N; j++) {
      fin >> ipt[i][j];
    }
  }
  k = 0;
  init(N * M);
  for (i = 1; i <= M; i++) {
    for (j = 1; j <= N; j++) {
      k++;
      if (j > 1) {
        if (!(ipt[i][j] & 1)) {
          merge(k, k - 1);
        }
      }
      if (i < N) {
        if (!(ipt[i][j] & 8)) {
          merge(k, k + N);
        }
      }
    }
  }
  fout << cnt << endl << mx_room << endl;
  int ans = 0, w = 0, s = 0, a, b, c;
  char ch = 'N';
  k = 0;
  for (i = 1; i <= M; i++) {
    for (j = 1; j <= N; j++) {
      k++;
      if (j < N) {
        if (ipt[i][j] & 4) {
          a = find(k);
          b = find(k+1);
          if (a != b) {
            c = uf_cnt[a] + uf_cnt[b];
            if (c > ans) {
              ans = c;
              w = j;
              s = i;
              ch = 'E';
            } else if (c == ans) {
              if (j < w || (j == w && i > s)) {
                s = i;
                w = j;
                ch = 'E';
              }
            }
          }
        }
      }
      if (i > 1) {
        if (ipt[i][j] & 2) {
          a = find(k);
          b = find(k - N);
          if (a != b) {
            c = uf_cnt[a] + uf_cnt[b];
            if (c > ans) {
              ans = c;
              w = j;
              s = i;
              ch = 'N';
            } else if (c == ans) {
              if (j < w || (j == w && i > s)) {
                s = i;
                w = j;
                ch = 'N';
              } else if (j == w && i == s) {
                ch = 'N';
              }
            }
          }
        }
      }
    }
  }
  fout << ans << endl << s << " " << w << " " << ch << endl;
  return 0;
}
