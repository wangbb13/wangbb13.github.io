#include <iostream>
#include <algorithm>
using namespace std;

const int Bound = 1002;

struct point {
  int x, y;
} pn[Bound];
int px[Bound], py[Bound], q[Bound];
int N, w, h, s, ans;

bool cmp(point a, point b) {
  return a.x < b.x;
}

void check() {
  sort(pn, pn + s, cmp);
  int h = 0, t = -1, j = 1;
  for (int i = 0; i < s - 1; i++) {
    while (h <= t && q[h] <= i) h++;
    while (j < s && (h > t || pn[q[h]].y >= pn[j].x - pn[i].x)) {
      q[++t] = j++;
      while (h < t && pn[q[t]].y <= pn[q[t-1]].y) {
        q[t-1] = q[t];
        t--;
      }
    }
    int w = min(pn[q[h]].y, pn[s-1].x - pn[i].x);
    ans = max(ans, w);
  }
}

int main() {
  int i, j, k;
  cin >> N >> w >> h;
  for (i = 0; i < N; i++) {
    cin >> px[i] >> py[i];
  }
  ans = 0;
  for (i = 0; i < N; i++) {
    int x0 = px[i];
    int y0 = py[i];
    // > x0
    s = 0;
    for (j = 0; j < N; j++) {
      if (px[j] > x0) {
        pn[s++] = (point){py[j], px[j] - x0};
      }
    }
    pn[s++] = (point){h, w - x0};
    pn[s++] = (point){0, w - x0};
    check();
    for (j = 0; j < s; j++) {
      pn[j].x = h - pn[j].x;
    }
    check();
    // < x0
    s = 0;
    for (j = 0; j < N; j++) {
      if (px[j] < x0) {
        pn[s++] = (point){py[j], x0 - px[j]};
      }
    }
    pn[s++] = (point){h, x0};
    pn[s++] = (point){0, x0};
    check();
    for (j = 0; j < s; j++) {
      pn[j].x = h - pn[j].x;
    }
    check();
    // > y0
    s = 0;
    for (j = 0; j < N; j++) {
      if (py[j] > y0) {
        pn[s++] = (point){px[j], py[j] - y0};
      }
    }
    pn[s++] = (point){w, h - y0};
    pn[s++] = (point){0, h - y0};
    check();
    for (j = 0; j < s; j++) {
      pn[j].x = w - pn[j].x;
    }
    check();
    // < y0
    s = 0;
    for (j = 0; j < N; j++) {
      if (py[j] < y0) {
        pn[s++] = (point){px[j], y0 - py[j]};
      }
    }
    pn[s++] = (point){w, y0};
    pn[s++] = (point){0, y0};
    check();
    for (j = 0; j < s; j++) {
      pn[j].x = w - pn[j].x;
    }
    check();
  }
  cout << ans << endl;
  return 0;
}