// note1: array of struct, memory has assigned, just modify it
// note2: big int add, first compute high digit, then current digit
#include <iostream>
using namespace std;

typedef struct bigInt {
  int digit[20];
  int size;
} BigInt;

// c = a + b
void add(BigInt& a, BigInt& b, BigInt& c) {
  for (int i = 19; i > 0; i--) {
    c.digit[i-1] += (c.digit[i] + a.digit[i] + b.digit[i]) / 10;
    c.digit[i] = (c.digit[i] + a.digit[i] + b.digit[i]) % 10;
  }
  c.digit[0] = (c.digit[0] + a.digit[0] + b.digit[0]) % 10;
  for (int i = 0; i < 20; i++) {
    if (c.digit[i] != 0) {
      c.size = 20 - i;
      return;
    }
  }
}

int main() {
  BigInt dp[51][51];
  int n, m, x1, y1, x2, y2;
  cin >> n >> m >> x1 >> y1 >> x2 >> y2;
  int i, j;
  for (i = 0; i < 51; i++) {
    for (j = 0; j < 51; j++) {
      dp[i][j].size = 0;
      for (int k = 0; k < 20; k++) {
        dp[i][j].digit[k] = 0;
      }
    }
  }
  for (i = 1; i <= n; i++) {
    dp[i][1].size = 1;
    dp[i][1].digit[19] = 1;
  }
  for (i = 1; i <= m; i++) {
    dp[1][i].size = 1;
    dp[1][i].digit[19] = 1;
  }
  for (i = 2; i <= n; i++) {
    for (j = 2; j <= m; j++) {
      if (i >= y1 && i <= y2 && j >= x1 && j <= x2) {
        dp[i][j].size = 0;
        dp[i][j].digit[19] = 0;
      } else {
        add(dp[i][j-1], dp[i-1][j], dp[i][j]);
      }
    }
  }
  for (i = (20 - dp[n][m].size); i < 20; i++) {
    cout << dp[n][m].digit[i];
  }
  cout << endl;
  return 0;
}
