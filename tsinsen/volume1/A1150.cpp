#include <iostream>
#include <algorithm>
using namespace std;

int fig[10003];
int N, M;

void add_one() {
  int tmp, i, j;
  if (fig[N-2] < fig[N-1]) {
    tmp = fig[N-2];
    fig[N-2] = fig[N-1];
    fig[N-1] = tmp;
  } else {
    i = N-1;
    while (i > 0 && fig[i-1] > fig[i]) { i--; }
    if (i == 0) {
      return;
    }
    i--;
    for (j = N-1; j > i; j--) {
      if (fig[j] > fig[i]) {
        tmp = fig[j];
        fig[j] = fig[i];
        fig[i] = tmp;
        break;
      }
    }
    i++;
    j = N-1;
    while (i < j) {
      tmp = fig[i];
      fig[i] = fig[j];
      fig[j] = tmp;
      i++;
      j--;
    }
  }
}

int main() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> fig[i];
  }
  for (int i = 0; i < M; i++) {
    // next_permutation(fig, fig+N);
    add_one();
  }
  for (int i = 0; i < N; i++) {
    cout << fig[i] << " ";
  }
  cout << endl;
  return 0;
}