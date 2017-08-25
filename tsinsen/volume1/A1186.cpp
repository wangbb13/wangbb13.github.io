#include <iostream>
#include <cmath>
using namespace std;

void deal(int n) {
  int p[11];
  int i = 0, j = 0;
  do {
    p[i++] = n % 10;
    n /= 10;
  } while (n > 0);
  while (j < i && p[j] == 0) {
    j++;
  }
  while (j < i) {
    cout << p[j++];
  }
}

int main() {
  int n;
  cin >> n;
  if (n == 0) {
    cout << 0 << endl;
    return 0;
  }
  if (n < 0) {
    cout << "-";
    deal(-n);
  } else {
    deal(n);
  }
  cout << endl;
  return 0;
}