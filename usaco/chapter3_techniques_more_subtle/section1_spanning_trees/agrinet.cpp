/*
ID: wangbb21
LANG: C++
TASK: agrinet
 */
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct my_tuple {
  int i, j, w;
} T[5100];

int uf[105] = {0};

void init() {
  for (int i = 1; i <= 100; i++) {
    uf[i] = i;
  }
}

int find(int x) {
  return (x == uf[x]) ? (x) : (uf[x] = find(uf[x]));
}

void merge(int x, int y) {
  int a = find(x), b = find(y);
  if (a != b) {
    uf[a] = b;
  }
}

bool cmp(my_tuple a, my_tuple b) {
  return a.w < b.w;
}

int main() {
  ofstream fout("agrinet.out");
  ifstream fin("agrinet.in");
  int N, p = 0, ans = 0, idx = 0;
  fin >> N;
  for (int i = 1; i <= N; i++) {
    int j, k;
    for (j = 1; j <= i; j++) {
      fin >> k;
    }
    for (; j <= N; j++) {
      fin >> k;
      T[p].i = i;
      T[p].j = j;
      T[p].w = k;
      p++;
    }
  }
  sort(T, T + p, cmp);
  init();
  for (int x = 0; x < N - 1; x++) {
    while (find(T[idx].i) == find(T[idx].j)) idx ++;
    ans += T[idx].w;
    merge(T[idx].i, T[idx].j);
    idx ++;
  }
  fout << ans << endl;
  return 0;
}
