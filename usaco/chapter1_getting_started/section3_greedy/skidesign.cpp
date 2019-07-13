/*
ID: wangbb21
LANG: C++
TASK: skidesign
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

int hill[1000];
int N, ans = 0x7fffffff;

int main() {
  ofstream fout("skidesign.out");
  ifstream fin("skidesign.in");
  int i, j, mi = ans, mx = -1, sum;
  fin >> N;
  for (i = 0; i < N; i++) {
    fin >> hill[i];
    mi = min(mi, hill[i]);
    mx = max(mx, hill[i]);
  }
  for (i = mi; i <= mx; i++) {
    sum = 0;
    for (j = 0; j < N; j++) {
      if (hill[j] > i) {
        sum += (hill[j] - i) * (hill[j] - i);
      } else if (i - hill[j] > 17) {
        sum += (i - hill[j] - 17) * (i - hill[j] - 17);
      }
    }
    ans = min(ans, sum);
  }
  fout << ans << endl;
  return 0;
}
