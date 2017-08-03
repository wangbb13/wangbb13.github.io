#include <iostream>
#include <cstdio>
using namespace std;

int main() {
  char input[13];
  cin >> input;
  int sum = 0, i, p = 1;
  for (i = 0; i < 11; i++) {
    if (input[i] != '-') {
      sum += p * (input[i] - '0');
      p++;
    }
  }
  sum = sum % 11;
  if ((sum == (input[12]-'0')) || (sum == 10 && input[12] == 'X')) {
    cout << "Right" << endl;
  } else {
    if (sum == 10) {
      input[12] = 'X';
    } else {
      input[12] = ('0' + sum);
    }
    printf("%s\n", input);
  }
  return 0;
}