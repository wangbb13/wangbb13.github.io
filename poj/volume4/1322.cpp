#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

/*
 * 可以近似..., 非战之罪也, line 31
 */

int main(int argc, char const *argv[])
{
  int M, N, cur, pre, i, j, k, step;
  double C;
  vector< vector<double> > P(2, vector<double>(103, 0.0));
  while (true) {
    cin >> C;
    if (C == 0) {
      break;
    }
    cin >> N >> M;
    if (N == 0 && M == 0) {
      cout << setiosflags(ios::fixed) << setprecision(3) << 1.0 << endl;
    } else if (N == 0 || M > C) {
      cout << setiosflags(ios::fixed) << setprecision(3) << 0.0 << endl;
    } else {
      P[0].assign(103, 0.0);
      P[1].assign(103, 0.0);
      cur = 0;
      pre = 1;
      P[0][1] = 1.0;
      N = (N > 1000) ? (1000 + N % 2) : N;
      step = (N % 2 == 1) ? (M % 2) : (1 - (M % 2));
      for (i = 2; i <= N; i++) {
        step = 1 - step;
        cur = 1 - cur;
        pre = 1 - pre;
        // P[cur][0] = P[pre][1] * (double)(1 / C);
        // for (j = 1; j < C; j++) {
        //   P[cur][j] = P[pre][j-1] * (double)((C-j+1)/C) + P[pre][j+1] * ((j+1)/C);
        // }
        // P[cur][C] = P[pre][C-1] * (double)(1 / C);
        if (step == 0) {
          P[cur][0] = P[pre][1] * (double)(1 / C);
        } else {
          P[cur][1] = P[pre][0] + P[pre][2] * (double)(2 / C);
        }
        for (j = step + 2; j < C; j += 2) {
          P[cur][j] = P[pre][j-1] * (double)((C-j+1)/C) + P[pre][j+1] * ((j+1)/C);
        }
        if (j == C) {
          P[cur][C] = P[pre][C-1] * (double)(1 / C);
        }
      }
      cout << setiosflags(ios::fixed) << setprecision(3) << P[cur][M] << endl;
    }
  }
  return 0;
}