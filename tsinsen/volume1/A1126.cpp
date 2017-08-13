#include <iostream>
#include <string>
#include <cmath>
#include <queue>
using namespace std;

typedef struct e {
  int idx, len;
  int map[22];
} E;

int table[22][22];
string word[22];
int N;
queue<E> myQ;

int main() {
  int i, j, k;
  char h;
  cin >> N;
  for (i = 0; i < N; i++) {
    cin >> word[i];
  }
  cin >> h;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      int val, li = word[i].size(), lj = word[j].size(), add = 0;
      for (val = 1; val < min(li, lj); val++) {
        if (word[i].substr(li-val, val) == word[j].substr(0, val)) {
          add = val;
          break;
        }
      }
      if (add > 0) {
        table[i][j] = lj - add;
      } else {
        table[i][j] = -1;
      }
    }
  }
  for (i = 0; i < N; i++) {
    if (word[i][0] == h) {
      E e = {i, word[i].size(), {0}};
      e.map[i]++;
      myQ.push(e);
    }
  }
  E last; k = 0;
  while (!myQ.empty()) {
    last = myQ.front();
    k = max(k, last.len);
    myQ.pop();
    for (i = 0; i < N; i++) {
      if (table[last.idx][i] > -1 && last.map[i] < 2) {
        E e = {i, table[last.idx][i] + last.len, {0}};
        for (j = 0; j < N; j++) {
          e.map[j] = last.map[j];
        }
        e.map[i]++;
        myQ.push(e);
      }
    }
  }
  cout << k << endl;
  return 0;
}