#include <iostream>
#include <cmath>
using namespace std;

int tag[2][100];
int src[100];
int ti = 0;

int gcd(int a, int b) {
  while (b) {
    int r = b;
    b = a % b;
    a = r;
  }
  return a;
}

// n > 1
void decom(int n) {
  while (n > 1) {
    bool flag = true;
    for (int i = 2; i <= sqrt(n); i++) {
      if (n % i == 0) {
        if (tag[0][ti] == 0) {
          tag[0][ti] = i;
          tag[1][ti] = 1;
        } else if (tag[0][ti] == i) {
          tag[1][ti]++;
        } else {
          ti++;
          tag[0][ti] = i;
          tag[1][ti] = 1;
        }
        n /= i;
        flag = false;
        break;
      }
    }
    if (flag) {
      if (tag[0][ti] == 0) {
        tag[0][ti] = n;
        tag[1][ti] = 1;
      } else if (tag[0][ti] == n) {
        tag[1][ti]++;
      } else {
        ti++;
        tag[0][ti] = n;
        tag[1][ti] = 1;
      }
      break;
    }
  }
}

bool contain(int k) {
  for (int i = 0; i <= ti; i++) {
    int num = tag[0][i], j = 0;
    while (k > 0 && k % num == 0) {
      j++;
      k /= num;
    }
    if (j == 0) {
      return false;
    }
    src[i] = j;
  }
  return true;
}

int cacu() {
  int ans = -1;
  for (int i = 0; i <= ti; i++) {
    if (tag[1][i] <= src[i]) {
      ans = max(ans, 1);
    } else {
      ans = max(ans, tag[1][i] / src[i] + (tag[1][i] % src[i] != 0));
    }
  }
  return ans;
}

int main() {
  int n, m1, m2, x;
  int i, j, k, r;
  int ans = -1;
  cin >> n >> m1 >> m2;
  if (m1 == 1) {
    for (i = 0; i < n; i++) {
      cin >> x;
    }
    cout << 1 << endl;
    return 0;
  }
  decom(m1);
  for (i = 0; i <= ti; i++) {
    tag[1][i] *= m2;
  }
  j = 2147483647;
  for (i = 0; i < n; i++) {
    cin >> k;
    if (k == 1) {
      continue;
    }
    if (!contain(k)) {
      continue;
    }
    r = cacu();
    if (r < j) {
      j = r;
      ans = i+1;
    }
  }
  cout << ans << endl;
  return 0;
}