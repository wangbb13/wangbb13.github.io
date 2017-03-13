#include <iostream>
// #include <climits>
#include <string>
#include <cmath>
using namespace std;

#define INF 1000000000

int kingMove[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
int knightMove[8][2] = {{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};
int kingMap[64][64];
int knightMap[64][64];

bool ok(int x, int y) {
  if (x >= 0 && x < 8 && y >= 0 && y < 8) {
    return true;
  }
  return false;
}

void getXY(int p, int& x, int& y) {
  x = p % 8;
  y = p / 8;
}

int getPosition(int x, int y) {
  return (8 * y + x);
}

void initMap() {
  int i, j, k;
  for (i = 0; i < 64; i++) {
    for (j = 0; j < 64; j++) {
      kingMap[i][j] = INF;
      knightMap[i][j] = INF;
    }
    kingMap[i][i] = 0;
    knightMap[i][i] = 0;
    int x, tx, y, ty, next;
    getXY(i, x, y);
    for (k = 0; k < 8; k++) {
      tx = x + kingMove[k][0];
      ty = y + kingMove[k][1];
      if (ok(tx, ty)) {
        next = getPosition(tx, ty);
        kingMap[i][next] = 1;
      }
      tx = x + knightMove[k][0];
      ty = y + knightMove[k][1];
      if (ok(tx, ty)) {
        next = getPosition(tx, ty);
        knightMap[i][next] = 1;
      }
    }
  }
}

void floyd() {
  int i, j, k;
  for (k = 0; k < 64; k++) {
    for (i = 0; i < 64; i++) {
      for (j = 0; j < 64; j++) {
        kingMap[i][j] = min((kingMap[i][k] + kingMap[k][j]), (kingMap[i][j]));
        knightMap[i][j] = min((knightMap[i][k] + knightMap[k][j]), (knightMap[i][j]));
      }
    }
  }
}

int main(int argc, char const *argv[])
{
  string s;
  int pNum, sSize, minMove = INF, sum;
  int position[64];
  initMap();
  floyd();
  cin >> s;
  sSize = s.size();
  pNum = 0;
  for (int i = 0; i < sSize; i += 2) {
    position[pNum++] = s[i] - 'A' + (s[i+1] - '1') * 8;
  }
  for (int dst = 0; dst < 64; dst++) {
    for (int m = 0; m < 64; m++) {
      for (int k = 1; k < pNum; k++) {
        sum = 0;
        for (int i = 1; i < pNum; i++) {
          sum += knightMap[position[i]][dst];
        }
        sum += kingMap[position[0]][m];
        sum += knightMap[position[k]][m] + knightMap[m][dst];
        sum -= knightMap[position[k]][dst];
        minMove = min(minMove, sum);
      }
    }
  }
  cout << minMove << endl;
  system("pause");
  return 0;
}