#include <iostream>
using namespace std;

#define max(a, b) ((a) > (b) ? (a) : (b))

int dp[101][61][61];
int status[61];
int numois[61];
int legalnos;

int numofones(int i) {
  int ans = 0;
  while (i) {
    i &= (i-1);
    ans++;
  }
  return ans;
}

void initstatus(int m) {
  int index = 0;
  for (int i = 0; i < (1 << m); i++) {
    if (!(i & (i << 1)) && !(i & (i << 2))) {
      status[index] = i;
      numois[index++] = numofones(i);
    }
  }
  legalnos = index;
}

int main(int argc, char const *argv[])
{
  int n, m, i, j, k, p, ans = 0;
  char map[101][11];
  int initmap[101];
  cin >> n >> m;
  initstatus(m);
  for (i = 0; i < n; i++) {
    cin >> map[i];
    initmap[i] = 0;
    for (j = 0; j < m; j++) {
      if (map[i][j] == 'P') {
        initmap[i] += (1 << (m - j - 1));
      }
    }
  }
  for (i = 0; i < n; i++) {
    for (j = 0; j < legalnos; j++) {
      for (k = 0; k < legalnos; k++) {
        dp[i][j][k] = -1;
      }
    }
  }
  for (i = 0; i < legalnos; i++) {
    if (!(status[i] & (~initmap[0]))) {
      dp[0][i][0] = numois[i];
    }
  }
  for (i = 1; i < n; i++) {
    for (j = 0; j < legalnos; j++) {
      if (!(status[j] & (~initmap[i]))) {   // 第i行状态为j是合法的
        for (k = 0; k < legalnos; k++) {
          if (!(status[k] & (~initmap[i-1])) && !(status[j] & status[k])) {   // 第i-1行状态为k是合法的
            for (p = 0; p < legalnos; p++) {
              if ((dp[i-1][k][p] > 0) && !(status[j] & status[p])) {
                dp[i][j][k] = max(dp[i][j][k], (dp[i-1][k][p] + numois[j]));
              }
            }
          }
        }
      }
    }
  }
  for (i = 0; i < legalnos; i++) {
    for (j = 0; j < legalnos; j++) {
      ans = max(ans, dp[n-1][i][j]);
    }
  }
  cout << ans << endl;
  return 0;
}