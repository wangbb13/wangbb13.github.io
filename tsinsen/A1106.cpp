#include <iostream>
using namespace std;

int main() {
  char input[30] = {0};
  unsigned long long int m = 0;
  int n = 0, p = 0;
  int output[100] = {0};
  int i, j, k;
  cin >> input;
  i = 0;
  while (input[i] != '<') {
    i++;
  }
  for (i++; input[i] != '>'; i++) {
    n = n * 10 + (input[i] - '0');
  }
  j = i;
  for (i = 0; input[i] != '<'; i++) {
    m = m * n + (input[i] - '0');
  }
  for (i = j+1; input[i] != 0; i++) {
    p = p * 10 + (input[i] - '0');
  }
  i = 0;
  do {
    output[i++] = (int)(m % p);
    m /= p;
  } while (m);
  for (k = 0; k <= j; k++) {
    cout << input[k];
  }
  cout << "=";
  for (i--; i >= 0; i--) {
    cout << output[i];
  }
  cout << "<" << p << ">" << endl;
  return 0;
}