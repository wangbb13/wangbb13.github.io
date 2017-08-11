/*
ID: wangbb21
LANG: C++
TASK: crypt1
 */
#include <iostream>
#include <fstream>
using namespace std;

int dig[10] = {0};
int map[10] = {0};
int N;

bool in(int n) {
  int x, i;
  do {
    x = n % 10;
    if (map[x] == 0) {
      return false;
    }
    n /= 10;
  } while (n > 0);
  return true;
}

int main() {
  ofstream fout("crypt1.out");
  ifstream fin("crypt1.in");
  int i, j, k, r, s, num1, num2, part1, part2, res, ans = 0;
  fin >> N;
  for (i = 0; i < N; i++) {
    fin >> dig[i];
    map[dig[i]] = 1;
  }
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      for (k = 0; k < N; k++) {
        for (r = 0; r < N; r++) {
          for (s = 0; s < N; s++) {
            num1 = dig[i] + dig[j] * 10 + dig[k] * 100;
            if (num1 > 99 && num1 < 1000) {
              num2 = dig[r] + dig[s] * 10;
              if (num2 > 9 && num2 < 100) {
                part1 = dig[r] * num1;
                if (part1 > 99 && part1 < 1000 && in(part1)) {
                  part2 = dig[s] * num1;
                  if (part2 > 99 && part2 < 1000 && in(part2)) {
                    res = num1 * num2;
                    if (res > 999 && res < 10000 && in(res)) {
                      ans++;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  fout << ans << endl;
  return 0;
}
