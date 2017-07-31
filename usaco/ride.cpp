/*
ID: wangbb21
LANG: C++
PROG: ride
 */
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
  ofstream fout("ride.out");
  ifstream fin("ride.in");
  int a = 1, b = 1;
  char str1[10], str2[10];
  fin >> str1 >> str2;
  int str1_len = strlen(str1);
  int str2_len = strlen(str2);
  for (int i = 0; i < str1_len; i++) {
    a *= (int)(str1[i] - 'A' + 1);
  }
  a %= 47;
  for (int i = 0; i < str2_len; i++) {
    b *= (int)(str2[i] - 'A' + 1);
  }
  b %= 47;
  if (a == b) {
    fout << "GO" << endl;
  } else {
    fout << "STAY" << endl;
  }
  return 0;
}