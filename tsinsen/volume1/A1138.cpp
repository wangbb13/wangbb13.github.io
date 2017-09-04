#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;

struct Pair {
  int x, y;
};

Pair airport[401];
double graph[401][401] = {-1.0};
double shor[401] = {0};
int flag[401] = {0};
int S, T, apc = 1;

double distancec(Pair a, Pair b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void rectangle(int x1, int y1, int x2, int y2, int x3, int y3, int t) {
  int temp = apc;
  airport[apc++] = (Pair){x1, y1};
  airport[apc++] = (Pair){x2, y2};
  airport[apc++] = (Pair){x3, y3};
  double a = distancec(airport[temp], airport[temp + 1]);
  double b = distancec(airport[temp], airport[temp + 2]);
  double c = distancec(airport[temp + 1], airport[temp + 2]);
  int x, y;
  if (a > max(b, c)) {  // (x3, y3)
    x = x1 + x2 - x3;
    y = y1 + y2 - y3;
  } else if (b > max(a, c)) {   // (x2, y2)
    x = x1 + x3 - x2;
    y = y1 + y3 - y2;
  } else {  // (x1, y1)
    x = x2 + x3 - x1;
    y = y2 + y3 - y1;
  }
  airport[apc++] = (Pair){x, y};
  graph[temp][temp + 1] = graph[temp + 1][temp] = a * t;
  graph[temp][temp + 2] = graph[temp + 2][temp] = b * t;
  graph[temp][temp + 3] = graph[temp + 3][temp] = c * t;
  graph[temp + 1][temp + 2] = graph[temp + 2][temp + 1] = c * t;
  graph[temp + 1][temp + 3] = graph[temp + 3][temp + 1] = b * t;
  graph[temp + 2][temp + 3] = graph[temp + 3][temp + 2] = a * t;
}

void cacuFly() {
  int end = S * 4, a;
  for (int i = 1; i < S; i++) {
    int base = i * 4 - 3;
    for (int j = 0; j < 4; j++) {
      a = base + j;
      for (int k = 4 * i + 1; k <= end; k++) {
        double dis = distancec(airport[a], airport[k]);
        graph[a][k] = graph[k][a] = dis * T;
      }
    }
  }
}

double shortestPath(int x, int y) {   // from x airport to y city
  memset(flag, 0, sizeof(flag));
  flag[x] = 1;
  int end = 4 * S, i, j, k;
  for (i = 1; i < x; i++) {
    shor[i] = graph[x][i];
  }
  shor[x] = 0.;
  for (i++; i <= end; i++) {
    shor[i] = graph[x][i];
  }
  for (i = 1; i < end; i++) {
    int p;
    double mi = 2000000000.0;
    for (j = 1; j <= end; j++) {
      if (flag[j] == 0 && shor[j] < mi) {
        mi = shor[j];
        p = j;
      }
    }
    flag[p] = 1;
    for (j = 1; j <= end; j++) {
      if (flag[j] == 0) {
        shor[j] = min(shor[j], shor[p] + graph[p][j]);
      }
    }
  }
  i = y * 4 - 3;
  double ans = shor[i];
  for (j = 0; j < 4; j++) {
    k = i + j;
    ans = min(ans, shor[k]);
  }
  return ans;
}

int main() {
  int A, B, i, j, k;
  int x1, y1, x2, y2, x3, y3, t;
  cin >> S >> T >> A >> B;
  for (i = 0; i < S; i++) {
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> t;
    rectangle(x1, y1, x2, y2, x3, y3, t);
  }
  cacuFly();
  i = A * 4 - 3;
  double ans = shortestPath(i, B);
  for (j = 1; j < 4; j++) {
    ans = min(ans, shortestPath(i + j, B));
  }
  printf("%.1f\n", ans);
  return 0;
}

/*
3 10 1 3
1 1 1 3 3 1 30
2 5 7 4 5 2 1
8 6 8 8 11 6 3
 */