#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

bool comp(pair<int, int> a, pair<int, int> b) {
  return a.first < b.first;
}

int main() {
  vector< pair<int, int> > subway;
  int L, M, ans = 0;
  int i, j, k;
  cin >> L >> M;
  for (i = 0; i < M; i++) {
    cin >> j >> k;
    subway.push_back(pair<int, int>(j, k));
  }
  sort(subway.begin(), subway.end(), comp);
  j = subway[0].first;
  k = subway[0].second;
  for (i = 1; i < subway.size(); i++) {
    if (subway[i].first <= k) {
      k = max(subway[i].second, k);
    } else {
      ans += (k - j + 1);
      j = subway[i].first;
      k = subway[i].second;
    }
  }
  ans += (k - j + 1);
  cout << (L + 1 - ans) << endl;
  return 0;
}