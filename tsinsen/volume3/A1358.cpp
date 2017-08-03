#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
  int n, m;
  int i, j, k;
  int ans = 0, round;
  int a, b, c, d;
  bool left, right, up, down;
  int arity;  // 
  int curI, curJ, curD; // 0: up 1: down 2: left 3: right -1: o
  int map[103][103];
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      cin >> map[i][j];
    }
  }
  while (true) {
    round = 0;
    for (i = 1; i < n-1; i++) {
      for (j = 1; j < m-1; j++) {
        curI = i, curJ = j, curD = -1;
        while (true) {
          a = map[curI-1][curJ] - map[curI][curJ];
          b = map[curI+1][curJ] - map[curI][curJ];
          c = map[curI][curJ-1] - map[curI][curJ];
          d = map[curI][curJ+1] - map[curI][curJ];
          up = a > 0; down = b > 0;
          left = c > 0; right = d > 0;
          arity = up + down + left + right;
          if (arity == 4) {
            round += min(min(a,b), min(c,d));
            
          } else if (arity > 1) {

          } else {

          }
        }
      }
    }
    if (round == 0) {
      break;
    } else {
      ans += round;
    }
  }
  cout << ans << endl;
  return 0;
}