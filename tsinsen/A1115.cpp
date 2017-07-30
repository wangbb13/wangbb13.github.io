#include <iostream>
#include <cmath>
using namespace std;

#define END 100

typedef struct bigInt {
  int a[100];
  int size;
} BigInt;

void show(BigInt ans) {
  for (int i = END - ans.size; i < END; i++) {
    cout << ans.a[i];
  }
  cout << endl;
}

BigInt add(BigInt a, BigInt b) {
  BigInt ans = {{0}, 0};
  int hi = END - max(a.size, b.size);
  int i;
  for (i = END-1; i >= hi; i--) {
    ans.a[i-1] = (ans.a[i] + a.a[i] + b.a[i]) / 10;
    ans.a[i] = (ans.a[i] + a.a[i] + b.a[i]) % 10;
  }
  if (ans.a[i] > 0) {
    ans.size = END - i;
  } else {
    ans.size = END - i - 1;
  }
  return ans;
}

BigInt mul_s(BigInt a, int b) {
  BigInt ans = {{0}, 0};
  if (b == 0) {
    return ans;
  }
  int i, hi = END - a.size;
  for (i = END - 1; i >= hi; i--) {
    ans.a[i-1] = (ans.a[i] + b * a.a[i]) / 10;
    ans.a[i] = (ans.a[i] + b * a.a[i]) % 10;
  }
  if (ans.a[i] > 0) {
    ans.size = END - i;
  } else {
    ans.size = END - i - 1;
  }
  return ans;
}

// b shorter
BigInt mul(BigInt a, int b) {
  BigInt l1 = {{0}, 0}, l2 = {{0}, 0};
  if (b < 10) {
    return mul_s(a, b);
  } else {
    l1 = mul_s(a, b % 10);
    l2 = mul_s(a, b / 10);
    l2.size++;
    for (int i = END - l2.size; i < END-1; i++) {
      l2.a[i] = l2.a[i+1];
    }
    l2.a[END-1] = 0;
    return add(l1, l2);
  }
}

int main() {
  int n;
  BigInt ans = {{0}, 0};
  BigInt x, y;
  cin >> n;
  x.size = 1;
  x.a[END-1] = 1;
  ans = add(ans, x);
  for (int i = 1; i < n; i++) {
    y = mul(x, i+1);
    x = y;
    ans = add(ans, x);
  }
  show(ans);
  return 0;
}