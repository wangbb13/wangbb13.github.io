#include <iostream>
#include <string.h>
using namespace std;

#define U 200000
#define I 100000

int res[U];
int r = 0;
char inp[I];

void clear() {
  for (int i = 0; i < U; i++) {
    res[i] = 0;
  }
  r = 0;
}

int main() {
  int n, l, t, i, j, p, m = 7;
  cin >> n;
  while (n--) {
    clear();
    cin >> inp;
    l = strlen(inp);
    if (l == 1 && inp[0] == '0') {
      cout << 0 << endl;
      continue;
    }
    t = 0;
    p = 0;
    for (i = l - 1; i >= 0; i--) {
      if (inp[i] >= '0' && inp[i] <= '9') {
        j = (int)(inp[i] - '0');
      } else {
        j = 10 + (int)(inp[i] - 'A');
      }
      t ^= (j << p);
      p += 4;
      while (t > m) {
        res[r++] = (t & m);
        t >>= 3;
        p -= 3;
      }
    }
    while (t > 0) {
      res[r++] = (t & m);
      t >>= 3;
    }
    for (i = r - 1; i >= 0; i--) {
      cout << res[i];
    }
    cout << endl;
  }
  return 0;
}