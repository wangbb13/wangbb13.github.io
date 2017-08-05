/*
ID: wangbb21
LANG: C++
TASK: barn1
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(pair<int, int> a, pair<int, int> b) {
  return a.first > b.first;
}

int main() {
  ofstream fout("barn1.out");
  ifstream fin("barn1.in");
  vector<int> ipt(200);
  vector< pair<int,int> > stall(200);
  vector<int> ind(50);
  int m, s, c, i, j, ans = 0;
  fin >> m >> s >> c;
  for (i = 0; i < c; i++) {
    fin >> ipt[i];
  }
  if (m >= c) {
    fout << c << endl;
    return 0;
  }
  sort(ipt.begin(), ipt.begin() + c);
  for (i = 0; i < c-1; i++) {
    stall[i].first = ipt[i+1] - ipt[i];
    stall[i].second = i;
  }
  sort(stall.begin(), stall.begin() + c - 1, comp);
  for (i = 0; i < m-1; i++) {
    ind[i] = stall[i].second;
  }
  sort(ind.begin(), ind.begin() + m - 1);
  j = 0;
  for (i = 0; i < m-1; i++) {
    ans += ipt[ind[i]] - ipt[j] + 1;
    j = ind[i] + 1;
  }
  ans += ipt[c-1] - ipt[j] + 1;
  fout << ans << endl;
  return 0;
}
