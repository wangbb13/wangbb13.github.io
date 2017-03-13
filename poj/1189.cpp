#include <iostream>
using namespace std;

__int64 gcd(__int64 a, __int64 b) { return a == 0 ? b : gcd(b % a, a); }

int main(int argc, char const *argv[])
{
  char map[51][51];
  __int64 prob[51][51][2];
  int n, m, i, j;
  __int64 a, b, d;
  cin >> n >> m;
  for (i = 0; i < n; i++) {
    for (j = 0; j < (i+1); j++) {
      cin >> map[i][j];
      prob[i][j][0] = 0;
      prob[i][j][1] = 0;
    }
  }
  for (i = 0; i < 51; i++) {
    prob[50][i][0] = 0;
    prob[50][i][1] = 0;
  }
  prob[0][0][0] = 1;  // molecular
  prob[0][0][1] = 1;  // denominator
  for (i = 0; i < n; i++) {
    for (j = 0; j < (i+1); j++) {
      if (map[i][j] == '*') {
        prob[i+1][j][0] += prob[i][j][0];
        prob[i+1][j][1]  = prob[i][j][1] * 2;
        prob[i+1][j+1][0] += prob[i][j][0];
        prob[i+1][j+1][1]  = prob[i][j][1] * 2;
      } else if (map[i][j] == '.') {
        prob[i+2][j+1][0] = prob[i][j][0] * 4;
        prob[i+2][j+1][1] = prob[i][j][1] * 4;
        prob[i+1][j][1] = prob[i][j][1] * 2;
        prob[i+1][j+1][1] = prob[i][j][1] * 2;
      }
    }
  }
  a = prob[n][m][0];
  b = prob[n][m][1];
  d = gcd(a, b);
  cout << (a / d) << "/" << (b / d) << endl;
  system("pause");
  return 0;
}


/*
int gcd(int x, int y) {
  if (y == 0) 
    return x;
  if (x < y) 
    return gcd(y, x);
  else 
    return gcd(y, x % y);
}
 */