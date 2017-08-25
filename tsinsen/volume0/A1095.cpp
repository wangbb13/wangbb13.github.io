#include <iostream>
using namespace std;

int room[] = {0, 120, 40, 85, 50, 100, 140, 70, 100};
int flag[] = {0, 1, 1, 1, 1, 1, 1, 1, 1};
int cnt = 0;
int n[4], res[4];

void deal(int i) {
  if (i == 4) {
    for (int j = 0; j < 4; j++) {
      cout << res[j] << " ";
    }
    cout << endl;
    cnt++;
    return;
  }
  for (int j = 1; j < 9; j++) {
    if (flag[j] == 1 && room[j] >= n[i]) {
      res[i] = j;
      flag[j] = 0;
      deal(i+1);
      flag[j] = 1;
    }
  }
}

int main() {
  for (int i = 0; i < 4; i++) {
    cin >> n[i];
  }
  deal(0);
  if (cnt == 0) {
    cout << -1 << endl;
  }
  return 0;
}