#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

#define min(a, b) ((a) < (b) ? (a) : (b))
int map[8][8];
int nn;
double avgx = 0, minVal = INT_MAX;
double record[8][8][8][8];

void init_record() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      for (int k = 0; k < 8; k++) {
        for (int m = 0; m < 8; m++) {
          record[i][j][k][m] = -1;
        }
      }
    }
  }
} 

double sum(int x0, int y0, int x1, int y1) {
  if (record[x0][y0][x1][y1] != -1) {
    return record[x0][y0][x1][y1];
  }
  double r = 0;
  for (int i = x0; i <= x1; i++) {
    for (int j = y0; j <= y1; j++) {
      r += map[i][j];
    }
  }
  record[x0][y0][x1][y1] = pow((r - avgx), 2);
  return record[x0][y0][x1][y1];
}

void solution(int x0, int y0, int x1, int y1, int n, double sigma) {
  int i, j, times;
  double temp;
  // int times = x1 - x0 + y1 - y0 + 1;
  // if (times >= n) {
  if (n == 2) {
    for (i = x0; i < x1; i++) {
      temp = sigma + sum(x0, y0, i, y1) + sum(i+1, y0, x1, y1);
      minVal = min(minVal, temp);
    }
    for (j = y0; j < y1; j++) {
      temp = sigma + sum(x0, y0, x1, j) + sum(x0, j+1, x1, y1);
      minVal = min(minVal, temp);
    }
    return;
  }
  for (i = x0; i < x1; i++) {
    times = i - x0 + y1 - y0 + 1;
    if (times >= n-1) {
      solution(x0, y0, i, y1, n-1, (sigma + sum(i+1, y0, x1, y1)));
    }
    times = x1 - i + y1 - y0;
    if (times >= n-1) {
      solution(i+1, y0, x1, y1, n-1, (sigma + sum(x0, y0, i, y1)));
    }
  }
  for (j = y0; j < y1; j++) {
    times = x1 - x0 + j - y0 + 1;
    if (times >= n-1) {
      solution(x0, y0, x1, j, n-1, (sigma + sum(x0, j+1, x1, y1)));
    }
    times = x1 - x0  + y1 - j;
    if (times >= n-1) {
      solution(x0, j+1, x1, y1, n-1, (sigma + sum(x0, y0, x1, j)));
    }
  }
  // }
}

int main(int argc, char const *argv[])
{
  int i, j;
  cin >> nn;
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      cin >> map[i][j];
      avgx += map[i][j];
    }
  }
  avgx /= nn;
  init_record();
  solution(0, 0, 7, 7, nn, 0);
  minVal = sqrt(minVal / nn);
  // cout << setprecision(4) << minVal << endl;
  printf("%.3f\n", minVal);
  system("pause");
  return 0;
}