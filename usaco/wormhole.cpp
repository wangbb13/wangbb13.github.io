/*
ID: wangbb21
LANG: C++
TASK: wormhole
 */
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int N, ans = 0;
vector< pair<int, int> > ipt;
int map[12];

// 注意细节！！
void deal(int s) {
  if (s == N) {
    int i, j, k, x, y, cnt;
    for (i = 0; i < N; i++) {
      j = i;
      cnt = 0;
      while (true) {
        cnt++;
        if (cnt > 12) {
          ans++;
          return;
        }
        x = ipt[map[j]].first;
        y = ipt[map[j]].second;
        bool flag = true;
        int mi = 0x7fffffff;   // 注意细节！！
        for (k = 0; k < N; k++) {
          if (ipt[k].first > x && ipt[k].second == y) {
            flag = false;
            if (ipt[k].first < mi) {
              mi = ipt[k].first;
              j = k;
            }
          }
        }
        if (flag) {
          break;
        }
      }
    }
    return;
  }
  int i = 0, j;
  while (map[i] != -1) { i++; }
  for (j = i+1; j < N; j++) {
    if (map[j] == -1) {
      map[i] = j;
      map[j] = i;
      deal(s+2);
      map[j] = -1;
      map[i] = -1;
    }
  }
}

int main() {
  ofstream fout("wormhole.out");
  ifstream fin("wormhole.in");
  int i, j, k;
  for (i = 0; i < 12; i++) {
    map[i] = -1;
  }
  fin >> N;
  for (i = 0; i < N; i++) {
    fin >> j >> k;
    ipt.push_back(pair<int, int>(j, k));
  }
  deal(0);
  fout << ans << endl;
  return 0;
}
