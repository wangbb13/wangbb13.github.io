#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char a[10], b[10], c[10];
int pa = 0;

void deal(int mi, int mj, int ei, int ej) {
  if (mi > mj) {
    return;
  }
  a[pa++] = c[ej];
  int i;
  for (i = mi; i <= mj; i++) {
    if (b[i] == c[ej]) {
      break;
    }
  }
  deal(mi, i-1, ei, ei + i - 1 - mi);
  deal(i+1, mj, ei + i - mi, ej - 1);
}

int main() {
  cin >> b >> c;
  int len = strlen(b);
  deal(0, len-1, 0, len-1);
  printf("%s\n", a);
  return 0;
}