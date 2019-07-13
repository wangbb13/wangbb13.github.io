/*
ID: wangbb21
LANG: C++
TASK: cowtour
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

int N;
double inf = 10000000002.;
struct point {
  double x, y;
} P[155];
char cmap[155][155];
int uf[155];
double dis[155][155];

void init() {
  for (int i = 0; i < N; i++) {
    uf[i] = i;
  }
}

int find(int x) {
  return (x == uf[x]) ? (x) : (uf[x] = find(uf[x]));
}

void merge(int x, int y) {
  int a = find(x);
  int b = find(y);
  if (a != b) {
    uf[a] = b;
  }
}

double cacu(point a, point b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double mx(int x, int y, double a) {
  double rtn = 0.;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if (find(x) == find(i) && find(y) == find(j)) {
        rtn = max(dis[x][i] + a + dis[y][j], rtn);
      }
    }
  }
  return rtn;
}

int main() {
  ofstream fout("cowtour.out");
  ifstream fin("cowtour.in");
  int i, j, k;
  fin >> N;
  init();
  for (i = 0; i < N; i++) {
    fin >> P[i].x >> P[i].y;
  }
  fin.getline(cmap[i], 155);
  for (i = 0; i < N; i++) {
    fin.getline(cmap[i], 155);
  }
  for (i = 0; i < N; i++) {
    dis[i][i] = 0.;
    for (j = i+1; j < N; j++) {
      if (cmap[i][j] == '1') {
        merge(i, j);
        dis[i][j] = dis[j][i] = cacu(P[i], P[j]);
      } else {
        dis[i][j] = dis[j][i] = inf;
      }
    }
  }
  for (k = 0; k < N; k++) {
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        if (dis[i][k] < inf && dis[k][j] < inf && (dis[i][j] > dis[i][k] + dis[k][j])) {
          dis[i][j] = dis[i][k] + dis[k][j];
        }
      }
    }
  }
  double ans = 0.;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (dis[i][j] < inf) {
        ans = max(ans, dis[i][j]);
      }
    }
  }
  double res = inf;
  for (i = 0; i < N; i++) {
    for (j = i+1; j < N; j++) {
      if (find(i) != find(j)) {
        res = min(res, mx(i, j, cacu(P[i], P[j])));
      }
    }
  }
  fout << std::fixed << setprecision(6) << max(res, ans) << endl;
  return 0;
}