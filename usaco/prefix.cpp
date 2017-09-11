/*
ID: wangbb21
LANG: C++
TASK: prefix
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int dp[200002] = {0};
string dict[202];
string S = "";
int dLen = 0;
int mDic = 0;

int main() {
  ofstream fout("prefix.out");
  ifstream fin("prefix.in");
  string str;
  while (true) {
    fin >> str;
    if (str == ".") {
      break;
    }
    dict[dLen++] = str;
    mDic = max(mDic, (int)str.size());
  }
  while (fin >> str) {
    S = S + str;
  }
  int i, j, k, ans = 0, len = S.size();
  dp[0] = 1;
  for (i = 1; i <= len; i++) {
    if (i > mDic) {
      bool flag = true;
      for (j = i - mDic; j < i; j++) {
        if (dp[j] == 1) {
          flag = false;
          break;
        }
      }
      if (flag) {
        break;
      }
    }
    for (j = 0; j < dLen; j++) {
      k = dict[j].size();
      if (k <= (i + 1)) {
        if ((dp[i - k] == 1) && (dict[j] == S.substr(i - k, k))) {
          dp[i] = 1;
          ans = i;
          break;
        }
      }
    }
  }
  fout << ans << endl;
  return 0;
}
