#include <iostream>
#include <queue>
using namespace std;

int map[1002] = {0};

int main() {
  int M, N, i, j, cnt = 0, ans = 0;
  queue<int> mQ;
  cin >> M >> N;
  for (i = 0; i < N; i++) {
    cin >> j;
    if (map[j] == 0) {
      if (cnt < M) {
        cnt++;
      } else {
        map[mQ.front()] = 0;
        mQ.pop();
      }
      map[j] = 1;
      mQ.push(j);
      ans++;
    }
  }
  cout << ans << endl;
  return 0;
}