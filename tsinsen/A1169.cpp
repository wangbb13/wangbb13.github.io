#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

int dp[1003] = {0}, color[1003] = {0}, input[1003] = {0};
int matrix[1003][1003] = {0};
int n;

void dfs(int i, int c) {
  color[i] = c;
  for (int j = 1; j <= n; j++) {
    if (matrix[i][j]) {
      if (color[j] == 0) {
        dfs(j, 3-c);
      } else if (color[j] == c) {
        cout << 0 << endl;
        exit(0);
      }
    }
  }
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> input[i];
  }
  dp[n+1] = INT_MAX;
  for (int i = n; i >= 1; i--) {
    dp[i] = min(input[i], dp[i+1]);
  }
  for (int i = 1; i < n; i++) {
    for (int j = i+1; j <= n; j++) {
      if (input[i] < input[j] && dp[j+1] < input[i]) {
        matrix[i][j] = 1;
        matrix[j][i] = 1;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (color[i] == 0) {
      dfs(i, 1);
    }
  }
  int on = 1;
  stack<int> s1, s2;
  for (int i = 1; i <= n; i++) {
    if (color[i] == 1) {
      s1.push(input[i]);
      cout << "a ";
    } else {
      s2.push(input[i]);
      cout << "c ";
    }
    while (true) {
      if (!s1.empty() && s1.top() == on) {
        s1.pop();
        cout << "b ";
      } else if (!s2.empty() && s2.top() == on) {
        s2.pop();
        cout << "d ";
      } else {
        break;
      }
      on++;
    }
  }
  return 0;
}
