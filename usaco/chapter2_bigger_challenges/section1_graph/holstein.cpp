/*
ID: wangbb21
LANG: C++
TASK: holstein
 */
#include <iostream>
#include <fstream>
using namespace std;

int type[26] = {0};
int scoop[16][26] = {0};
int res[16] = {0};
int V, G;

ofstream fout("holstein.out");
ifstream fin("holstein.in");

void deal(int p, int s, int n) {
  if (s == n) {
    bool flag = true;
    for (int i = 1; i <= V; i++) {
      int val = 0;
      for (int j = 1; j <= s; j++) {
        val += scoop[res[j]][i];
      }
      if (val < type[i]) {
        flag = false;
        break;
      }
    }
    if (flag) {
      fout << n;
      for (int i = 1; i <= s; i++) {
        fout << " " << res[i];
      }
      fout << endl;
      exit(0);
    }
    return;
  }
  for (int i = p; i <= G; i++) {
    res[s + 1] = i;
    deal(i + 1, s + 1, n);
    res[s + 1] = 0;
  }
}

int main() {
  
  int i, j;
  fin >> V;
  for (i = 1; i <= V; i++) {
    fin >> type[i];
  }
  fin >> G;
  for (i = 1; i <= G; i++) {
    for (j = 1; j <= V; j++) {
      fin >> scoop[i][j];
    }
  }
  for (i = 1; i <= G; i++) {
    deal(1, 0, i);
  }
  return 0;
}
