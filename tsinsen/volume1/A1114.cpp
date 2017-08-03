#include <iostream>
using namespace std;

bool legal(int a, int b, int c) {
  int map[10] = {0};
  map[a/100] = 1;
  map[a%10] = 1;
  map[(a/10)%10] = 1;
  map[b/100] = 1;
  map[b%10] = 1;
  map[(b/10)%10] = 1;
  map[c/100] = 1;
  map[c%10] = 1;
  map[(c/10)%10] = 1;
  for (int i = 1; i <= 9; i++) {
    if (map[i] == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int i, j, k, s;
  for (i = 1; i < 4; i++) {
    for (j = 1; j <= 9; j++) {
      for (k = 1; k <= 9; k++) {
        if (i != j && i != k) {
          s = i * 100 + j * 10 + k;
          if (legal(s, s*2, s*3)) {
            cout << s << " " << s*2 << " " << s*3 << endl;
          }
        }
      }
    }
  }
  return 0;
}