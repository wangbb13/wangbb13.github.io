#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
  if (a.second == b.second) {
    return a.first < b.first;
  }
  return a.second > b.second;
}

int main() {
  int i, j, N, R, Q, r, s, p, n;
  cin >> N >> R >> Q;
  n = 2 * N;
  vector< pair<int, int> > f(n, pair<int, int>(0, 0));
  vector< pair<int, int> > F(n, pair<int, int>(0, 0));
  vector<int> c(n, 0);
  for (i = 0; i < n; i++) {
    cin >> f[i].second;
    f[i].first = i;
  }
  sort(f.begin(), f.end(), cmp);
  for (i = 0; i < n; i++) {
    cin >> c[i];
  }
  for (i = 0; i < R; i++) {
    for (j = 0; j < n; j += 2) {
      if (c[f[j].first] > c[f[j+1].first]) {
        f[j].second++;
      } else {
        f[j+1].second++;
        if (cmp(f[j+1], f[j])) {
          pair<int, int> temp = f[j];
          f[j] = f[j+1];
          f[j+1] = temp;
        }
      }
    }
    // sort(f.begin(), f.end(), cmp);
    r = 0; s = 1; p = 0;
    while (r < n && s < n) {
      if (cmp(f[r], f[s])) {
        F[p++] = f[r];
        r += 2;
      } else {
        F[p++] = f[s];
        s += 2;
      }
    }
    while (r < n) {
      F[p++] = f[r];
      r += 2;
    }
    while (s < n) {
      F[p++] = f[s];
      s += 2;
    }
    f = F;
  }
  cout << (f[Q-1].first+1) << endl;
  return 0;
}