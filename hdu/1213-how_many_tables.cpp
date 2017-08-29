#include <iostream>
using namespace std;

int uf[1001] = {0};
int N, M, ans;

void init(int x) {
  for (int i = 1; i <= x; i++) {
    uf[i] = i;
  }
}

int find(int x) {
  return x == uf[x] ? x : uf[x] = find(uf[x]);
}

void merge(int x, int y) {
  int a = find(x), b = find(y);
  if (a != b) {
    uf[a] = b;
    ans--;
  }
}

int main() {
  int T, i, j, k;
  cin >> T;
  while (T--) {
    cin >> N >> M;
    init(N);
    ans = N;
    for (i = 0; i < M; i++) {
      cin >> j >> k;
      merge(j, k);
    }
    cout << ans << endl;
  }
  return 0;
}