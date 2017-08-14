#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int dis(int x1, int y1, int x2, int y2) {
  return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

bool comp(pair<int, int> a, pair<int, int> b) {
  return a.first > b.first;
}

vector< pair<int, int> > dp(100000);

int main() {
  int x1, y1, x2, y2;
  int N, x, y, i;
  int mx, ans;
  cin >> x1 >> y1 >> x2 >> y2 >> N;
  for (i = 0; i < N; i++) {
    cin >> x >> y;
    dp[i] = pair<int, int>(dis(x1, y1, x, y), dis(x2, y2, x, y));
  }
  sort(dp.begin(), dp.end(), comp);
  ans = dp[0].first;
  mx = -1;
  for (i = 1; i < N; i++) {
    mx = max(mx, dp[i-1].second);
    if (mx + dp[i].first < ans) {
      ans = mx + dp[i].first;
    }
  }
  cout << ans << endl;
  return 0;
}