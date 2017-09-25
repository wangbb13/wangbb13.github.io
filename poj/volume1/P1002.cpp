#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
using namespace std;

void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int* A, int l, int r) {
  int reserve_value = A[r];
  int i = l - 1, j;
  for (j = l; j < r; j++) {
    if (A[j] < reserve_value) {
      i++;
      swap(&A[i], &A[j]);
    }
  }
  swap(&A[++i], &A[r]);
  return i;
}

void quickSort(int* A, int l, int r) {
  if (l < r) {
    int m = partition(A, l, r);
    quickSort(A, l, m-1);
    quickSort(A, m+1, r);
  }
}

int main(int argc, char const *argv[])
{
  int n;
  int* A;
  char* s;
  int i, j, k, flag;
  scanf("%d", &n);
  s = (char*)malloc(sizeof(char) * 1024);
  A = (int*)malloc(sizeof(int) * (n + 1));
  // accept input
  for (i = 0; i < n; i++) {
    k = 0;
    scanf("%s", s);
    for (j = 0; j < strlen(s); j++) {
      if (isdigit(s[j])) {
        k = k * 10 + (s[j] - '0');
      } else if (isupper(s[j])) {
        k = k * 10 + (s[j] - 'A' - (s[j] > 'Q')) / 3 + 2;
      }
    }
    A[i] = k;
  } // end input
  sort(A, A + n);
  i = 0;
  flag = 0;
  while (i < n) {
    j = i + 1;
    while (j < n && A[j] == A[i]) {
      j++;
    }
    if ((j-i) > 1) {
      printf("%03d-%04d %d\n", (A[i] / 10000), (A[i] % 10000), (j-i));
      flag = 1;
    }
    i = j;
  }
  if (0 == flag) {
    printf("No duplicates.\n");
  }
  return 0;
}