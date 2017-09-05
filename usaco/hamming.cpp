/*
ID: wangbb21
LANG: C++
TASK: hamming
 */
#include <iostream>
#include <fstream>
using namespace std;

int N, B, D;
int A[256] = {0};

bool hamD(int a, int b) {
  int c = a ^ b, ans = 0;
  while (c) {
    ans++;
    c &= (c - 1);
  }
  return ans < D;
}

int main() {
  ofstream fout("hamming.out");
  ifstream fin("hamming.in");
  int i, j, k, r;
  fin >> N >> B >> D;
  k = 1 << B;
  i = 0;
  A[i] = 0;
  for (i = 1; i < N; i++) {
    for (j = A[i - 1] + 1; j < k; j++) {
      bool flag = true;
      for (r = 0; r < i; r++) {
        if (hamD(A[r], j)) {
          flag = false;
          break;
        }
      }
      if (flag) {
        A[i] = j;
        break;
      }
    }
  }
  i = 0;
  while (i < N) {
    fout << A[i];
    for (i++, j = 0; j < 9 && i < N; j++, i++) {
      fout << " " << A[i];
    }
    fout << endl;
  }
  return 0;
}
