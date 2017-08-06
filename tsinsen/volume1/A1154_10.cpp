#include <iostream>
#include <cassert>
using namespace std;

typedef struct bigInt {
  int al[100];
  int size;
} BigInt;

int mid[100][100];

void show(BigInt ans) {
  for (int i = (100 - ans.size); i < 100; i++) {
    cout << ans.al[i];
  }
  cout << endl;
}

BigInt add_one(BigInt a) {
  BigInt ans = a;
  ans.al[99] += 1;
  int i;
  for (i = 99; i >= (100 - ans.size); i--) {
    if (ans.al[i] > 10) {
      ans.al[i-1] += (ans.al[i] / 10);
      ans.al[i] %= 10;
    } else {
      break;
    }
  }
  if (i < (100 - ans.size) && ans.al[i] != 0) {
    ans.size++;
  }
  return ans;
}

BigInt mul(BigInt a, BigInt b) {
  assert (a.size == b.size);
  int i, j, k, r, l;
  for (i = 0; i < 100; i++) {
    for (j = 0; j < 100; j++) {
      mid[i][j] = 0;
    }
  }
  k = 99;
  l = 0;
  for (j = 99; j >= (100 - b.size); j--) {
    r = k;
    for (i = 99; i >= (100 - a.size); i--) {
      if (r > 0) {
        mid[l][r-1] = (mid[l][r] + b.al[j] * a.al[i]) / 10;
      }
      mid[l][r]     = (mid[l][r] + b.al[j] * a.al[i]) % 10;
      r--;
      if (r < 0) {
        break;
      }
    }
    k--;
    l++;
  }

  // cout << "debug" << endl;
  // k = 100; i = 100 - a.size;
  // for (l = 0; l < a.size; l++) {
  //   for (j = i; j < k; j++) {
  //     cout << mid[l][j] << " ";
  //   }
  //   cout << endl;
  //   i--; k--;
  // }
  // cout << "debug" << endl;

  BigInt ans = {{0}, 0};
  ans.size = a.size;
  k = 1;
  for (j = 99; j >= (100 - a.size); j--) {
    r = 0;
    for (i = 0; i < k; i++) {
      r += mid[i][j];
    }

    // cout << "debug" << endl;
    // cout << r << endl;
    // cout << "debug" << endl;

    if (j > 0) {
      ans.al[j-1] = (ans.al[j] + r) / 10;
    }
    ans.al[j]     = (ans.al[j] + r) % 10;
    k++;
  }
  return ans;
}

bool same(BigInt a, BigInt b) {
  if (a.size == b.size) {
    for (int i = 99; i >= (100 - a.size); i--) {
      if (a.al[i] != b.al[i]) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}

int main() {
  BigInt base = {{0}, 0};
  int i, j, k;
  char ch;
  i = 0;
  while ((ch = cin.get()) != ' ') {
    base.al[i++] = (int)(ch - '0');
  }
  cin >> k;
  for (j = 99; j >= (100 - k); j--) {
    base.al[j] = base.al[--i];
  }
  for (; j >= 0; j--) {
    base.al[j] = 0;
  }
  base.size = k;
  BigInt mlpl = base;
  BigInt ans = {{0}, 1};
  ans.al[99] = 1;
  // show(base);
  // show(mlpl);
  // show(ans);
  // cout << "====" << endl;
  // i = 0;
  while (true) {
    mlpl = mul(base, mlpl);
    // show(mlpl);
    if (same(base, mlpl)) {
      break;
    }
    ans = add_one(ans);
    // show(ans);
    // cout << "*******" << endl;
    // i++;
    // if (i == 5) {
    //   break;
    // }
  }
  show(ans);
  return 0;
}