#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const int BOUND = 300;

struct BigInt {
  int nums[300];
  int size;
};

void printBigInt(BigInt a) {
  for (int i = BOUND - a.size; i < BOUND; i++) {
    cout << a.nums[i];
  }
  cout << endl;
}

BigInt add(BigInt a, BigInt b) {
  BigInt ans = {{0}, 0};
  int end = BOUND - max(a.size, b.size);
  int i;
  for (i = BOUND - 1; i >= end; i--) {
    ans.nums[i - 1] = (ans.nums[i] + a.nums[i] + b.nums[i]) / 10;
    ans.nums[i]     = (ans.nums[i] + a.nums[i] + b.nums[i]) % 10;
  }
  ans.size = BOUND - i - 1;
  if (ans.nums[i] > 0) {
    ans.size += 1;
  }
  return ans;
}

BigInt mul_int(BigInt a, int b) {
  BigInt ans = {{0}, 0};
  int end = BOUND - a.size, i;
  for (i = BOUND - 1; i >= end; i--) {
    ans.nums[i - 1] = (ans.nums[i] + a.nums[i] * b) / 10;
    ans.nums[i]     = (ans.nums[i] + a.nums[i] * b) % 10;
  }
  ans.size = BOUND - i - 1;
  if (ans.nums[i] > 0) {
    ans.size += 1;
  }
  return ans;
}

BigInt mul_mi(BigInt a, int b) {
  BigInt ans = {{0}, 0};
  for (int i = BOUND - a.size; i < BOUND; i++) {
    ans.nums[i - b] = a.nums[i];
  }
  ans.size = a.size + b;
  return ans;
}

BigInt mul(BigInt a, BigInt b) {
  BigInt ans = {{0}, 0};
  if (a.size < b.size) {
    BigInt temp = a;
    a = b;
    b = temp;
  }
  int i, j = 0;
  for (i = BOUND - 1; i >= BOUND - b.size; i--) {
    BigInt c = mul_int(a, b.nums[i]);
    c = mul_mi(c, j);
    ans = add(ans, c);
    j++;
  }
  return ans;
}

BigInt expo(BigInt a, int n) {
  if (n == 0) {
    BigInt ans = {{0}, 0};
    ans.size = 1;
    ans.nums[BOUND - 1] = 1;
    return ans;
  } else if (n == 1) {
    return a;
  } else {
    BigInt ans = mul(a, a);
    ans = expo(ans, n / 2);
    if (n % 2 == 1) {
      ans = mul(ans, a);
    }
    return ans;
  }
}

int main() {
  char R[10];
  int i, j, k, n, dot;
  while(cin >> R >> n) {
  dot = 0;
  BigInt r = {{0}, 0};
  j = BOUND;
  for (i = 5; i >= 0; i--) {
    if (R[i] == '.') {
      dot = 5 - i;
    } else {
      r.nums[--j] = (int)(R[i] - '0');
    }
  }
  while (j < BOUND && r.nums[j] == 0) j++;
  if (j == BOUND) {
    cout << 0 << endl;
    return 0;
  }
  r.size = BOUND - j;
  BigInt ans = expo(r, n);
  dot *= n;
  if (dot == 0) {
    printBigInt(ans);
  } else if (dot < ans.size) {
    i = BOUND - ans.size;
    j = ans.size - dot;
    for (k = 0; k < j; k++) {
      cout << ans.nums[i++];
    }
    j = BOUND - 1;
    while (ans.nums[j] == 0) j--;
    if (i <= j) {
      cout << ".";
    }
    for (; i <= j; i++) {
      cout << ans.nums[i];
    }
    cout << endl;
  } else {
    cout << ".";
    j = dot - ans.size;
    for (k = 0; k < j; k++) {
      cout << 0;
    }
    j = BOUND - 1;
    while (ans.nums[j] == 0) j--;
    for (i = BOUND - ans.size; i <= j; i++) {
      cout << ans.nums[i];
    }
    cout << endl;
  }
}
  return 0;
}