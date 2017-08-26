#include <iostream>
#include <algorithm>
using namespace std;

// 首先考虑将怨气值最大的两个
// 罪犯分隔开，因此首先按照怨
// 气值降序排序，按照次序将两
// 个罪犯分隔开：如果分隔开后
// 两者处于同一集合，说明此时
// 即为答案，因为如果将两人分
// 开，那么势必会出现怨气值更
// 大的情况。

typedef struct e {
  int s, t, w;
} E;

E edges[100002];
int uf[40003];
int N, M;

int find(int x) {
  return x == uf[x] ? x : uf[x] = find(uf[x]);
}

void merge(int x, int y) {
  int xr = find(x), yr = find(y);
  uf[xr] = yr;
}

bool cmp(E a, E b) {
  return a.w > b.w;
}

int main() {
  int i, j, k;
  cin >> N >> M;
  for (i = 1; i <= 2 * N; i++) {
    uf[i] = i;
  }
  for (i = 0; i < M; i++) {
    cin >> edges[i].s >> edges[i].t >> edges[i].w;
  }
  sort(edges, edges + M, cmp);
  for (i = 0; i < M; i++) {
    if (find(edges[i].s) == find(edges[i].t)) {
      cout << edges[i].w << endl;
      return 0;
    }
    merge(edges[i].s, edges[i].t + N);
    merge(edges[i].t, edges[i].s + N);
  }
  cout << 0 << endl;
  return 0;
}