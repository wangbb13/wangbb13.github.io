#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main() {
  vector<int> pre(40, 0);
  vector<int> cur(40, 0);
  int n, i, j;
  cin >> n;
  if (n > 0) {
    cout << 1 << endl;
  }
  if (n > 1) {
    cout << 1 << " " << 1 << endl;
    pre[1] = 1;
    pre[2] = 1;
    for (i = 3; i <= n; i++) {
      cout << 1 << " ";
      cur[1] = 1;
      for (j = 2; j < i; j++) {
        cur[j] = pre[j] + pre[j-1];
        cout << cur[j] << " ";
      }
      cout << 1 << endl;
      cur[i] = 1;
      pre = cur;
    }
  }
  system("pause");
  return 0;
}