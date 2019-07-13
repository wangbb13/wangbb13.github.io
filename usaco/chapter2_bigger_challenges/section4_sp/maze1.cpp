/*
ID: wangbb21
LANG: C++
TASK: maze1
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

int map[210][92] = {0};
int val[210][92] = {0};
int sta[210][92] = {0};
int H, W, res, ans;
int dire[4][2] = {
  {-1, 0}, {0, 1}, {1, 0}, {0, -1}
};

struct triple {
  int x, y, s;
};

void init() {
  for (int i = 1; i < H; i += 2) {
    for (int j = 1; j < W; j += 2) {
      val[i][j] = 99999;
    }
  }
}

void ista() {
  for (int i = 0; i < H; i ++) {
    for (int j = 0; j < W; j ++) {
      sta[i][j] = 0;
    }
  }
}

bool legal(int x, int y) {
  if (x >= 0 && x < H && y >= 0 && y < W && map[x][y] == 0) {
    return true;
  }
  return false;
}

bool bound(int x, int y) {
  if ((x == 0) || (x == (H-1)) || (y == 0) || (y == (W-1))) {
    return true;
  }
  return false;
}

void bfs(vector< triple > nums) {
  int len = nums.size();
  if (len == 0) {
    return;
  } 
  vector< triple > next;
  for (int i = 0; i < len; i++) {
    int a = nums[i].x;
    int b = nums[i].y;
    int c = nums[i].s;
    for (int j = 0; j < 4; j++) {
      int x = a + dire[j][0];
      int y = b + dire[j][1];
      if (legal(x, y) && sta[x][y] == 0) {
        sta[x][y] = 1;
        triple t;
        t.x = x;
        t.y = y;
        t.s = c;
        if (x % 2 == 1 && y % 2 == 1) {
          t.s++;
          val[x][y] = min(t.s, val[x][y]);
        }
        next.push_back(t);
      }
    }
  }
  bfs(next);
}

int main() {
  ofstream fout("maze1.out");
  ifstream fin("maze1.in");
  int i, j, k = 0, a, b, x, y;
  char ch[100];
  fin >> W >> H;
  H = 2 * H + 1;
  W = 2 * W + 1;
  fin.getline(ch, sizeof(ch));
  for (i = 0; i < H; i++) {
    fin.getline(ch, sizeof(ch));
    for (j = 0; j < W; j++) {
      if (ch[j] == '+' || ch[j] == '-' || ch[j] == '|') {
        map[i][j] = 1;
      } else if (bound(i, j)) {
        if (k == 0) {
          a = i; b = j;
          k++;
        } else {
          x = i; y = j;
        }
      }
    }
  }
  ans = 0;
  init();
  vector< triple > ary(1);
  ary[0].x = a;
  ary[0].y = b;
  ary[0].s = 0;
  ista();
  sta[a][b] = 1;
  bfs(ary);
  ary[0].x = x;
  ary[0].y = y;
  ary[0].s = 0;
  ista();
  sta[x][y] = 1;
  bfs(ary);
  for (i = 1; i < H; i += 2) {
    for (j = 1; j < W; j += 2) {
      if (map[i][j] == 0) {
        ans = max(ans, val[i][j]);
      }
    }
  }
  fout << ans << endl;
  return 0;
}