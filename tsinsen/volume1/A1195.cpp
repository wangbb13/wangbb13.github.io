#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int N, M, K;
int D[1001] = {0};  // i站点到i+1站点所需时间
int P[1001] = {0};  // 从i站点出发时车上的人数
int down[1001] = {0};  // 在i站点下车人数 
int can[1001] = {0};   // 从i站点到i+1站点能够减少的费用

struct info {
  int t, a, b;
} f[10002];

bool cmp1(info x, info y) {
  if (x.a == y.a) {
    return x.t < y.t;
  } else {
    return x.a < y.a;
  }
}

int main() {
  int i, j, k, tim, ans = 0, mx = 0, xp;
  cin >> N >> M >> K;
  for (i = 1; i < N; i++) {
    cin >> D[i];
  }
  for (i = 0; i < M; i++) {
    cin >> f[i].t >> f[i].a >> f[i].b;
    down[f[i].b]++;
  }
  sort(f, f+M, cmp1);
  // 第一次上车
  i = 0;
  j = f[0].a; // 目前站点 
  tim = f[0].t; // 当前时刻
  P[j]++; // 当前站点的人数
  while (i < M && f[++i].a == j) {
    ans += P[j] * (f[i].t - tim);
    // cout << ans << endl;
    tim = f[i].t;
    P[j]++;
  }
  can[j] = P[j] * (min(D[j], K));
  for (j++; j <= N; j++) {
    ans += P[j-1] * D[j-1];
    P[j] = P[j-1] - down[j];
    tim += D[j-1];
    // if (j == 7) { cout << P[j] << " "; }
    if (j == f[i].a) {  // 在j站点有旅客上车
      k = 0;  // 在车到达前就已经到达站点的旅客人数
      while (i < M && f[i].a == j) {
        if (tim >= f[i].t) {
          ans += (tim - f[i].t);
          k++;
        } else {
          P[j] += k;  //加上已经到达的人数
          k = 0;
          ans += P[j] * (f[i].t - tim);
          tim = f[i].t;
          P[j]++;
        }
        // if (j == 7) { cout << k << " "; }
        i++;
      }
      P[j] += k;
    }
    // if (j == 7) { cout << P[j] << " "; }
    can[j] = P[j] * (min(D[j], K)); // 从i站点到i+1站点能够减少的时间
  }
  // cout << ans << endl;
  while (K > 0 && ans > 0) {
    mx = 0; xp = 0;
    for (j = f[0].a; j < N; j++) {
      if (can[j] > mx) {
        mx = can[j];
        xp = j;
      }
    }
    ans -= mx;
    K -= min(K, D[xp]);
    D[xp] = 0;
    // cout << mx << " " << xp << endl;
    // cout << P[6] << " " << P[7] << endl;
    for (j = f[0].a; j < N; j++) {
      can[j] = P[j] * (min(D[j], K));
    }
  }
  cout << ans << endl;
}