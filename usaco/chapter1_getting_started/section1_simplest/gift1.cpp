/*
ID: wangbb21
LANG: C++
TASK: gift1
 */
#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

int main() {
  ofstream fout("gift1.out");
  ifstream fin("gift1.in");
  map<string, int> ma;
  map<int, string> mb;
  int val[10] = {0};
  string str, str1;
  int i, j, k, r, np;
  fin >> np;
  for (i = 0; i < np; i++) {
    fin >> str;
    ma[str] = i;
    mb[i] = str;
  }
  for (i = 0; i < np; i++) {
    fin >> str >> j >> k;
    val[ma[str]] -= j;
    for (r = 0; r < k; r++) {
      fin >> str1;
      val[ma[str1]] += j / k;
    }
    if (k == 0) {
      val[ma[str]] += j;
    } else {
      val[ma[str]] += (j - k * (j / k));
    }
  }
  for (i = 0; i < np; i++) {
    fout << mb[i] << " " << val[i] << endl;
  }
  return 0;
}