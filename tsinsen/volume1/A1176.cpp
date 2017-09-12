#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int Up = 100002;
vector< vector<int> > f(Up);
vector< vector<int> > b(Up);
int visit[Up] = {0};
int price[Up] = {0};
int minpr[Up] = {0};
int N, M;

void dmi(int p, int v) {
  if (v >= minpr[p]) return;
  minpr[p] = v = min(v, price[p]);
  for (int i = 0; i < f[p].size(); i++) {
    dmi(f[p][i], v);
  }
}

void dfs(int p) {
  visit[p] = 1;
  for (int i = 0; i < b[p].size(); i++) {
    if (!visit[b[p][i]]) {
      dfs(b[p][i]);
    }
  }
}

int main() {
  int i, j, k, r, ans = 0;
  cin >> N >> M;
  for (i = 1; i <= N; i++) {
    cin >> price[i];
    minpr[i] = 200;
  }
  for (i = 0; i < M; i++) {
    cin >> j >> k >> r;
    f[j].push_back(k);
    b[k].push_back(j);
    if (r == 2) {
      f[k].push_back(j);
      b[j].push_back(k);
    }
  }
  dmi(1, price[1]);
  dfs(N);
  for (i = 1; i <= N; i++) {
    if (visit[i]) {
      ans = max(ans, price[i] - minpr[i]);
    }
  }
  cout << ans << endl;
  return 0;
}