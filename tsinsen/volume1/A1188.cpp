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
  int i, j, N, R, Q;
  cin >> N >> R >> Q;
  vector< pair<int, int> > f(2*N, pair<int, int>(0, 0));
  vector<int> c(2*N, 0);
  for (i = 0; i < 2*N; i++) {
    cin >> f[i].second;
    f[i].first = i;
  }
  sort(f.begin(), f.end(), cmp);
  for (i = 0; i < 2*N; i++) {
    cin >> c[i];
  }
  for (i = 0; i < R; i++) {
    for (j = 0; j < 2 * N; j += 2) {
      if (c[f[j].first] > c[f[j+1].first]) {
        f[j].second++;
      } else {
        f[j+1].second++;
      }
    }
    sort(f.begin(), f.end(), cmp);
  }
  cout << (f[Q-1].first+1) << endl;
  return 0;
}