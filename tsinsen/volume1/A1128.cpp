#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

char ipt[100] = {0};
int a, b, c, d;
char ch;

int main() {
  int i, j, k, len;
  scanf("%s", ipt);
  len = strlen(ipt);
  i = 0; j = 0;
  a = b = c = d = 0;
  while (ipt[i] != '=') {
    bool neg = false;
    if (ipt[i] == '-') {
      neg = true;
      i++; j++;
    }
    if (ipt[i] == '+') {
      i++; j++;
    }
    if (islower(ipt[i])) {
      ch = ipt[i];
      if (neg) {
        b -= 1;
      } else {
        b += 1;
      }
      i++; j = i;
      continue;
    }
    while (isdigit(ipt[j])) { j++; }
    int num = 0;
    for (k = i; k < j; k++) {
      num = num * 10 + (ipt[k] - '0');
    }
    if (islower(ipt[j])) {
      ch = ipt[j];
      if (neg) {
        b -= num;
      } else {
        b += num;
      }
      j++;
      i = j;
    } else {
      if (neg) {
        a -= num;
      } else {
        a += num;
      }
      i = j;
    }
  }
  i++;
  j = i;
  while (i < len) {
    bool neg = false;
    if (ipt[i] == '-') {
      neg = true;
      i++; j++;
    }
    if (ipt[i] == '+') {
      i++; j++;
    }
    if (islower(ipt[i])) {
      ch = ipt[i];
      if (neg) {
        d -= 1;
      } else {
        d += 1;
      }
      i++; j = i;
      continue;
    }
    while (isdigit(ipt[j])) { j++; }
    int num = 0;
    for (k = i; k < j; k++) {
      num = num * 10 + (ipt[k] - '0');
    }
    if (islower(ipt[j])) {
      ch = ipt[j];
      if (neg) {
        d -= num;
      } else {
        d += num;
      }
      j++;
      i = j;
    } else {
      if (neg) {
        c -= num;
      } else {
        c += num;
      }
      i = j;
    }
  }
  double ans = (double)(c - a) / (double)(b - d);
  if (ans == 0.) {
    ans = 0.;
  }
  printf("%c=%.3f\n", ch, ans);
  return 0;
}