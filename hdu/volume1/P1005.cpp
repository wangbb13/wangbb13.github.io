/*
 * Problem: f(n) = (A * f(n-1) + b * f(n-2)) % 7
 * Input  : A B n
 *          ...
 * Output : res
 * Notes  : pay attention to cycle, may not begin at the first position.
 */
#include <iostream>
using namespace std;

int nums[100];

int main() {
  int a, b, c, A, B, n, i, j, k, l;
  a = b = c = 1;
  while ((cin >> A >> B >> n) && A && B && n) {
    if (n < 3) { 
      cout << 1 << endl; 
      continue;
    }
    a = b = 1;
    nums[0] = nums[1] = 1;
    j = 2;
    l = 0;
    for (i = 3; i <= n; i++) {
      c = (A * b + B * a) % 7;
      a = b;
      b = c;
      nums[j++] = c;
      for (k = 0; k < j - 1; k++) {
        if (a == nums[k] && b == nums[k+1]) {
          l = j - k - 2;
          break;
        }
      }
      if (l) { break; }
    }
    if (i > n) { cout << c << endl; }
    else {
      i = ((n-k) % l) - 1;
      if (i < 0) { i += l; }
      cout << nums[i+k] << endl;
    }
  }
  return 0;
}