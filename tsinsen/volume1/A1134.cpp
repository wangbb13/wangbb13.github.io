#include <iostream>
using namespace std;

int main() {
  int N, i, k;
  cin >> N;
  for (i = 1; i < N; i++) {
    if (i * (i+1) / 2 >= N) {
      break;
    }
  }
  k = N - (i-1) * i / 2;
  if (i % 2 == 0) {
    cout << k << "/" << (i+1-k) << endl;
  } else {
    cout << (i+1-k) << "/" << k << endl;
  }
  return 0;
}