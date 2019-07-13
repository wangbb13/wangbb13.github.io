/*
ID: wangbb21
LANG: C++
TASK: milk
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(pair<int,int> a, pair<int,int> b) {
  return a.first < b.first;
}

int main() {
  ofstream fout("milk.out");
  ifstream fin("milk.in");
  vector< pair<int, int> > farm(5000);
  int n, m;
  int i, j, ans = 0;
  fin >> n >> m;
  for (i = 0; i < m; i++) {
    fin >> farm[i].first >> farm[i].second;
  }
  sort(farm.begin(), farm.end(), comp);
  i = 0;
  while (n > 0) {
    j = min(n, farm[i].second);
    n -= j;
    ans += j * farm[i].first;
    i++;
  }
  fout << ans << endl;
  return 0;
}
