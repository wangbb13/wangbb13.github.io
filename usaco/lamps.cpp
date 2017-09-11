/*
ID: wangbb21
LANG: C++
TASK: lamps
 */
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

ofstream fout("lamps.out");
ifstream fin("lamps.in");

string restr = "";
int N, C;
bool Im = true;

void deal() {
  vector<string> cur;
  string str = "";
  for (int i = 1; i <= N; i++) {
    str = str + "1";
  }
  cur.push_back(str);
  for (int i = 0; i < C; i++) {
    vector<string> next;
    set<string> mS;
    for (int j = 0; j < cur.size(); j++) {
      string ch = cur[j];
      string tm = ch;
      for (int k = 0; k < N; k++) {
        if (tm[k] == '0') {
          tm[k] = '1';
        } else {
          tm[k] = '0';
        }
      }
      if (mS.count(tm) <= 0) {
        mS.insert(tm);
        next.push_back(tm);
      }
      tm = ch;
      for (int k = 0; k < N; k += 2) {
        if (tm[k] == '0') {
          tm[k] = '1';
        } else {
          tm[k] = '0';
        }
      }
      if (mS.count(tm) <= 0) {
        mS.insert(tm);
        next.push_back(tm);
      }
      tm = ch;
      for (int k = 1; k < N; k += 2) {
        if (tm[k] == '0') {
          tm[k] = '1';
        } else {
          tm[k] = '0';
        }
      }
      if (mS.count(tm) <= 0) {
        mS.insert(tm);
        next.push_back(tm);
      }
      tm = ch;
      for (int k = 0; k < N; k += 3) {
        if (tm[k] == '0') {
          tm[k] = '1';
        } else {
          tm[k] = '0';
        }
      }
      if (mS.count(tm) <= 0) {
        mS.insert(tm);
        next.push_back(tm);
      }
    }
    cur = next;
  }
  set<string> Sm;
  vector<string> ans;
  for (int i = 0; i < cur.size(); i++) {
    string ch = cur[i];
    bool flag = true;
    for (int j = 0; j < N; j++) {
      if (restr[j] != '2' && restr[j] != ch[j]) {
        flag = false;
        break;
      }
    }
    if (flag) {
      if (Sm.count(ch) <= 0) {
        Sm.insert(ch);
        ans.push_back(ch);
        Im = false;
      }
    }
  }
  sort(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); i++) {
    fout << ans[i] << endl;
  }
}

int main() {
  fin >> N >> C;
  int i;
  for (i = 1; i <= N; i++) {
    restr = restr + "2";
  }
  while (true) {
    fin >> i;
    if (i == -1) {
      break;
    }
    restr[i - 1] = '1';
  }
  while (true) {
    fin >> i;
    if (i == -1) {
      break;
    }
    restr[i - 1] = '0';
  }
  deal();
  if (Im) {
    fout << "IMPOSSIBLE" << endl;
  }
  return 0;
}
