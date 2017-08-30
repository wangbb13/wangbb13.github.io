#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int ans[20] = {0}, mid[20] = {0};
int val[1001] = {0};
int mxv = 0, N, K;

void clear() {
  for (int i = 1; i < 1001; i++) {
    val[i] = 0x7fffffff;
  }
}

int cacu(int n) {
  if (n == 0) {
    return 0;
  }
  clear();
  int i = 1;
  while (true) {
    for (int j = 0; j < n && mid[j] <= i; j++) {
      val[i] = min(val[i], val[i - mid[j]] + 1);
    }
    if (val[i] > N) {
      return i-1;
    }
    i++;
  }
}

void search(int p) {
  if (p == K) {
    int v = cacu(K);
    if (v > mxv) {
      mxv = v;
      for (int i = 0; i < K; i++) {
        ans[i] = mid[i];
      }
    }
    return;
  }
  int cur_mxv = cacu(p);
  int low = (p == 0) ? 1 : mid[p - 1];
  for (int i = low; i <= cur_mxv + 1; i++) {
    mid[p] = i;
    search(p + 1);
  }
}

int main() {
  cin >> N >> K;
  search(0);
  for (int i = 0; i < K; i++) {
    cout << ans[i] << " ";
  }
  cout << endl << "MAX=" << mxv << endl;
  return 0;
}