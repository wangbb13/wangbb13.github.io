#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const int bound = 200002;

struct wv {
  int w, v;
} WV[bound];

struct ab {
  int l, r;
} AB[bound];

int N, M, MI, MX;
long long int S;
long long int num[bound], sum[bound];

long long int value(int th) {
  long long int ans = 0;
  memset(num, 0, sizeof(num));
  memset(sum, 0, sizeof(sum));
  for (int i = 1; i <= N; i++) {
    num[i] = num[i-1];
    sum[i] = sum[i-1];
    if (WV[i].w >= th) {
      num[i]++;
      sum[i] += WV[i].v;
    }
  }
  for (int i = 0; i < M; i++) {
    int l = AB[i].l, r = AB[i].r;
    ans += (num[r] - num[l-1]) * (sum[r] - sum[l-1]);
  }
  return ans;
}

void binDeal() {
  long long int vi = value(MI);
  if (vi <= S) {
    cout << (S - vi) << endl;
    return;
  }
  long long int vx = value(MX);
  if (vx >= S) {
    cout << (vx - S) << endl;
    return;
  }
  int l = MX, r = MI, mid;
  long long int vm;
  while (l > r+1) {
    mid = (l + r) / 2;
    vm  = value(mid);
    if (vm == S) {
      cout << 0 << endl;
      return;
    } else if (vm > S) {
      r = mid;
      vi = vm;
    } else {
      l = mid;
      vx = vm;
    }
  }
  long long int a = vi - S;
  long long int b = S - vx;
  if (a < b) {
    cout << a << endl;
  } else {
    cout << b << endl;
  }
}

int main() {
  cin >> N >> M >> S;
  MI = 107;
  MX = -1;
  for (int i = 1; i <= N; i++) {
    cin >> WV[i].w >> WV[i].v;
    MI = min(MI, WV[i].w);
    MX = max(MX, WV[i].w);
  }
  for (int i = 0; i < M; i++) {
    cin >> AB[i].l >> AB[i].r;
  }
  binDeal();
  return 0;
}