/*
ID: wangbb21
LANG: C++
TASK: dualpal
 */
#include <iostream>
#include <fstream>
using namespace std;

bool legal(int n, int b) {
  char al[32];
  int pi = 32;
  do {
    al[--pi] = n % b;
    n /= b;
  } while (n > 0);
  int i = pi, j = 31;
  while (i < j) {
    if (al[i] != al[j]) {
      return false;
    }
    i++;
    j--;
  }
  return true;
}

int main() {
  ofstream fout("dualpal.out");
  ifstream fin("dualpal.in");
  int n, s, i, j;
  fin >> n >> s;
  while (n > 0) {
    s++;
    j = 0;
    for (i = 2; i <= 10; i++) {
      if (legal(s, i)) {
        j++;
      }
      if (j > 1) {
        n--;
        fout << s << endl;
        break;
      }
    }
  }
  return 0;
}
