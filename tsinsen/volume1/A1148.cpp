#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef struct tp {
  int val, i, j;
} TP;

bool comp(TP a, TP b) {
  return a.val > b.val;
}

int main() {
  int M, N, K;
  int i, j, k, r, s, t, ans = 0;
  vector<TP> farm; 
  cin >> M >> N >> K;
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      cin >> k;
      farm.push_back((TP){k, i, j});
    }
  }
  sort(farm.begin(), farm.end(), comp);
  K -= 2;
  s = 0;
  i = 0; j = farm[0].j;
  while (K > 0) {
    k = farm[s].i; r = farm[s].j;
    t = abs(k - i) + abs(r - j) + k + 1;
    if (t <= K) {
      K -= (t - k);
      i = k; j = r;
      ans += farm[s].val;
      s++;
    } else {
      break;
    }
  }
  cout << ans << endl;
  return 0;
}