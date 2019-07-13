/*
ID: wangbb21
LANG: C++
TASK: preface
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string str[4][10] = {
  {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
  {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
  {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
  {"", "M", "MM", "MMM"}
};

int ans[7] = {0};
char rom[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

int main() {
  ofstream fout("preface.out");
  ifstream fin("preface.in");
  int N;
  fin >> N;
  for (int i = 1; i <= N; i++) {
    string num = "";
    num = num + str[3][i / 1000 % 10];
    num = num + str[2][i / 100 % 10];
    num = num + str[1][i / 10 % 10];
    num = num + str[0][i % 10];
    for (int j = 0; j < num.size(); j++) {
      for (int k = 0; k < 7; k++) {
        if (num[j] == rom[k]) {
          ans[k]++;
          break;
        }
      }
    }
  }
  for (int i = 0; i < 7; i++) {
    if (ans[i] > 0) {
      fout << rom[i] << " " << ans[i] << endl;
    }
  }
  return 0;
}