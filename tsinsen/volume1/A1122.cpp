#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;

int main() {
  vector< pair<double, double> > sta;
  double D1, C, D2, P, S, FL;
  int i, j, k, N;
  cin >> D1 >> C >> D2 >> P >> N;
  FL = C * D2;
  sta.push_back(pair<double, double>(0., P));
  for (i = 0; i < N; i++) {
    cin >> S >> P;
    sta.push_back(pair<double, double>(S, P));
  }
  sta.push_back(pair<double, double>(D1, 0.));
  for (i = 1; i < sta.size(); i++) {
    if (sta[i].first - sta[i-1].first > FL) {
      cout << "No Solution" << endl;
      return 0;
    }
  }
  double dri = 0., cost = 0., oil = 0., st = 0;
  while (dri < D1) {
    // 没有加油站了
    if (st == sta.size() - 2) {
      double need_o = ((sta[st+1].first - sta[st].first) / D2) - oil;
      cost += need_o * sta[st].second;
      break;
    }
    // 不加油
    double can_d = oil * D2, min_c = 1000000.;
    for (i = st+1; i < sta.size() - 1; i++) {
      if (sta[i].first - sta[st].first > can_d) {
        break;
      }
      if (sta[i].second < min_c) {
        min_c = sta[i].second;
        j = i;
      }
    }
    // 存在价格更低的加油站
    if (min_c < sta[st].second) {
      oil -= (sta[j].first - sta[st].first) / D2;
      st = j;
      dri += (sta[j].first - sta[st].first);
      continue;
    }
    // 加满油能否找到价格更低的
    min_c = 1000000.;
    for (i = st+1; i < sta.size() - 1; i++) {
      if (sta[i].first - sta[st].first > FL) {
        break;
      }
      if (sta[i].second < min_c) {
        min_c = sta[i].second;
        j = i;
      }
    }
    // 存在价格更低的
    if (min_c < sta[st].second) {
      double need_o = (sta[j].first - sta[st].first) / D2 - oil;
      cost += need_o * sta[st].second;
      dri += (sta[j].first - sta[st].first);
      st = j;
      oil = 0.;
      continue;
    }
    // 不存在, 能直接到终点
    if (D1 - sta[st].first <= FL) {
      double need_o = (D1 - sta[st].first) / D2 - oil;
      if (need_o > 0.) {
        cost += need_o * sta[st].second;
        break;
      }
    }
    // 不能直接到终点, 加满
    cost += (C - oil) * sta[st].second;
    oil = C - (sta[j].first - sta[st].first) / D2;
    dri += (sta[j].first - sta[st].first);
    st = j;
  }
  printf("%.2f\n", cost);
  return 0;
}