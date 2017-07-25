#include <iostream>
#include <cmath>
using namespace std;

bool isZ(int num) {
  if (num == 0 || num == 1) {
    return false;
  }
  for (int i = 2; i <= sqrt(num); i++) {
    if (num % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int hash[26] = {0};
  char input[103] = {0};
  cin >> input;
  int i, max = 0, min = 101;
  for (i = 0; input[i] != 0; i++) {
    hash[(int)(input[i] - 'a')]++;
  }
  for (i = 0; i < 26; i++) {
    if (hash[i] > max) {
      max = hash[i];
    }
    if (hash[i] < min && hash[i] != 0) {
      min = hash[i];
    }
  }
  if (isZ(max-min)) {
    cout << "Lucky Word" << endl;
    cout << max-min << endl;
  } else {
    cout << "No Answer" << endl << 0 << endl;
  }
  return 0;
}