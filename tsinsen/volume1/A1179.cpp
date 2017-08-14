#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int n, m;
int time[10001];

int main() {
  int i, j, ans = 0;
  cin >> n >> m;
  for (i = 0; i < n; i++) {
    cin >> time[i];
  }
  priority_queue<int> pQ;
  for (i = 0; i < m; i++) {
    pQ.push(-time[i]);
  }
  for (i = m; i < n; i++) {
    j = pQ.top();
    j -= time[i];
    pQ.pop();
    pQ.push(j);
  }
  for (i = 0; i < m; i++) {
    j = pQ.top();
    ans = min(ans, j);
    pQ.pop();
  }
  cout << (-ans) << endl;
  return 0;
}