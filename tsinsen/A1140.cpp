#include <iostream>
#include <cmath>
using namespace std;

int input[23];
int n, k;
int counter = 0;

bool isSu(int num) {
  if (num == 1 || num == 0) {
    return false;
  }
  for (int i = 2; i <= sqrt(num); i++) {
    if (num % i == 0) {
      return false;
    }
  }
  return true;
}

void deal(int t, int p, int s) {
  if (t == k) {
    if (isSu(s)) {
      counter++;
    }
    return;
  }
  for (int i = p; i < n; i++) {
    deal(t+1, i+1, s+input[i]);
  }
}

int main() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> input[i];
  }
  deal(0, 0, 0);
  cout << counter << endl;
  return 0;
}