#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

// 重要的特点：
// 如果能够灌溉干旱地区，那么
// 每个灌水长能够灌溉的干旱城市是一个区间
// 因此可以使用贪心策略

int N, M;
int city[502][502];
int f[502][502];
int leftt[502]  = {0};
int rightt[502] = {0};
int dry[502]   = {0};

int dire[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool legal(int x, int y, int a, int b) {
  if (a >= 1 && a <= N && b >= 1 && b <= M) {
    return city[x][y] > city[a][b];
  }
  return false;
}

int sat() {
  int ans = 0;
  for (int i = 1; i <= M; i++) {
    if (dry[i] == 0) {
      ans++;
    }
  }
  return ans;
}

int main() {
  int i, j, k, r;
  cin >> N >> M;
  for (i = 1; i <= N; i++) {
    for (j = 1; j <= M; j++) {
      cin >> city[i][j];
    }
  }
  for (i = 1; i <= M; i++) {
    // 优化点，不需要全部查找
    if (city[1][i] < city[1][i-1]) {
      continue;
    }
    memset(f, 0, sizeof(f));
    f[1][i] = 1;
    queue< pair<int, int> > mQ;
    mQ.push(pair<int, int>(1, i));
    while (!mQ.empty()) {
      int x = mQ.front().first;
      int y = mQ.front().second;
      mQ.pop();
      if (x == N) {
        dry[y] = 1;
        if (leftt[i] == 0 || y < leftt[i]) {
          leftt[i] = y;
        } 
        if (y > rightt[i]) {
          rightt[i] = y;
        }
      }
      for (j = 0; j < 4; j++) {
        int a = x + dire[j][0];
        int b = y + dire[j][1];
        if (legal(x, y, a, b) && f[a][b] == 0) {
          f[a][b] = 1;
          mQ.push(pair<int, int>(a, b));
          if (a == N) {
            dry[b] = 1;
            if (leftt[i] == 0 || b < leftt[i]) {
              leftt[i] = b;
            }
            if (b > rightt[i]) {
              rightt[i] = b;
            }
          }
        }
      }
    }
  }
  k = sat();
  if (k == 0) {
    cout << 1 << endl;
    // 贪心策略
    j = 1;
    r = 0;
    while (j <= M) {
      for (i = 1; i <= M; i++) {
        if (leftt[i] <= j && rightt[i] > r) {
          r = rightt[i];
        }
      }
      j = r + 1;
      k++;
    }
    cout << k << endl;
  } else {
    cout << 0 << endl << k << endl;
  }
  // system("pause");
  return 0;
}