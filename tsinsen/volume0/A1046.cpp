#include <iostream>
#include <string.h>
using namespace std;

char inp[105];

int main() {
  cin >> inp;
  int l = strlen(inp), i = 0, n, ans = 0;
  bool add = true;
  do {
    n = 0;
    while (i < l && inp[i] >= '0' && inp[i] <= '9') {
      n = n * 10 + (int)(inp[i] - '0');
      i++;
    }
    if (add) {
      ans += n;
    } else {
      ans -= n;
    }
    if (inp[i] == '+') {
      add = true;
    } else {
      add = false;
    }
    i++;
  } while (i < l && inp[i] != '=');
  cout << ans << endl;
  return 0;
}