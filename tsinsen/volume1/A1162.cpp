#include <iostream>
using namespace std;

typedef struct bigInt {
  int array[100];
  int size;
} BigInt;

// return: 2 * a + 2
BigInt add(BigInt a) {
  BigInt c = {{0},0};
  int p = 100 - a.size, i = 99;
  c.array[99] = 2;
  for (i; i >= p; i--) {
    c.array[i-1] += (c.array[i] + a.array[i] * 2) / 10;
    c.array[i] = (c.array[i] + a.array[i] * 2) % 10;
  }
  if (c.array[i] == 0) {
    c.size = 99 - i;
  } else {
    c.size = 100 - i;
  }
  return c;
}

int main() {
  int n, i;
  BigInt ans = {{0},0};
  cin >> n;
  for (i = 0; i < n; i++) {
    ans = add(ans);
  }
  for (i = 100 - ans.size; i < 100; i++) {
    cout << ans.array[i];
  }
  cout << endl;
  return 0;
}