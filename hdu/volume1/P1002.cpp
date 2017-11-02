/*
 * Problem: big integer add 
 * Input  : test cases
 *          a b
 *          ...
 * Output : for each case i:
 *            Case i:
 *            a + b = sum
 *            endl
 */
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cmath>
using namespace std;

#define LEN 1010
#define max(a,b) ((a) > (b) ? (a) : (b))

typedef struct bigInt {
  int ary[LEN];
  int size;
} BG;

BG add(BG a, BG b) {
  BG res = {{0}, 0};
  int i, k = LEN - max(a.size, b.size);
  for (i = LEN-1; i >= k; i--) {
    res.ary[i-1] = (res.ary[i] + a.ary[i] + b.ary[i]) / 10;
    res.ary[i]   = (res.ary[i] + a.ary[i] + b.ary[i]) % 10;
  }
  res.size = LEN - i;
  if (res.ary[i] == 0) {
    res.size--;
  }
  return res;
}

void showBG(BG a) {
  for (int i = LEN - a.size; i < LEN; i++) {
    cout << a.ary[i];
  }
  cout << endl;
}

int main() {
  char a[LEN], b[LEN];
  int t, lena, lenb, i, j, k = 1;
  cin >> t;
  while (t--) {
    cin >> a >> b;
    lena = strlen(a);
    lenb = strlen(b);
    BG ba = {{0}, 0};
    BG bb = {{0}, 0};
    ba.size = lena;
    bb.size = lenb;
    j = 0;
    for (i = LEN - lena; i < LEN; i++) {
      ba.ary[i] = (int)(a[j++] - '0');
    }
    j = 0;
    for (i = LEN - lenb; i < LEN; i++) {
      bb.ary[i] = (int)(b[j++] - '0');
    }
    cout << "Case " << (k++) << ":" << endl;
    printf("%s + %s = ", a, b);
    showBG(add(ba, bb));
    if (t) cout << endl;
  }
  return 0;
}