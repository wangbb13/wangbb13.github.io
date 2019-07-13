/*
ID: wangbb21
LANG: C++
TASK: palsquare
 */
#include <iostream>
#include <fstream>
using namespace std;

char al[32] = {0};
char sl[32] = {0};
int pi, ps;

bool legal(int n, int b) {
  pi = 32;
  do {
    if (n % b < 10) {
      al[--pi] = ('0' + (n % b));
    } else {
      al[--pi] = ('A' + (n % b - 10));
    }
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
  ofstream fout("palsquare.out");
  ifstream fin("palsquare.in");
  int base;
  fin >> base;
  for (int i = 1; i <= 300; i++) {
    legal(i, base);
    ps = pi;
    for (int j = pi; j < 32; j++) {
      sl[j] = al[j];
    }
    if (legal(i*i, base)) {
      for (int k = ps; k < 32; k++) {
        fout << sl[k];
      }
      fout << " ";
      for (int k = pi; k < 32; k++) {
        fout << al[k];
      }
      fout << endl;
    }
  }
  return 0;
}
