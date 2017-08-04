#include <iostream>
#include <cmath>
using namespace std;

#define M 500 

int number[M];
int p = M - 1;

int main() {
  int n, i, j, k, r, x;
  cin >> n;
  number[M-1] = 1;
  for (i = 0; i < n/3; i++) {
    k = 0; r = 0;
    for (j = M-1; j >= p; j--) {
      r = (number[j] * 8 + k) / 10;
      number[j] = (number[j] * 8 + k) % 10;
      k = r; 
    }
    if (r != 0 && p > 0) {
      number[--p] = r;
    }
  }
  if (n % 3 > 0) {
    if (n % 3 == 1) {
      x = 2;
    } else {
      x = 4;
    }
    k = 0; r = 0;
    for (j = M-1; j >= p; j--) {
      r = (number[j] * x + k) / 10;
      number[j] = (number[j] * x + k) % 10;
      k = r; 
    }
    if (r != 0) {
      number[--p] = r;
    }
  }
  i = M-1;
  while (number[i] == 0) { i--; }
  number[i]--;
  while ((++i) < M) { number[i] = 9; }
  cout << (int)(log(2.0) * n / log(10.0)) + 1 << endl;
  i = M-500;
  for (j = 0; j < 10; j++) {
    for (k = 0; k < 50; k++) {
      cout << number[i++];
    }
    cout << endl;
  }
  return 0;
}