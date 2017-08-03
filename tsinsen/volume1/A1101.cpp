#include <stdio.h>
#include <stdlib.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

int main(int argc, char const *argv[]) 
{
  int n, i, j, bi, bj;
  scanf("%d", &n);
  scanf("%d", &i);
  scanf("%d", &j);
  for (int y = 1; y <= n; y++) {
    printf("(%d,%d)", i, y);
  }
  printf("\n");
  for (int y = 1; y <= n; y++) {
    printf("(%d,%d)", y, j);
  }
  printf("\n");
  bi = min((i-1), (j-1));
  bj = j - bi;
  bi = i - bi;
  while (bi <= n && bj <= n) {
    printf("(%d,%d)", bi, bj);
    bi++;
    bj++;
  }
  printf("\n");
  bi = min((n-i), (j-1));
  bj = j - bi;
  bi = i + bi;
  while (bi >= 1 && bj <= n) {
    printf("(%d,%d)", bi, bj);
    bi--;
    bj++;
  }
  printf("\n");
  system("pause");
  return 0;
}