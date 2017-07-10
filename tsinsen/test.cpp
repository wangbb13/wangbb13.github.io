#include <iostream>
#include <string>
using namespace std;

int main() {
  string input;
  cin >> input;
  cout << (int)(input[1] - input[0]) << endl;
  input[0] -= 32;
  cout << input << endl;
  char a = input[0];
  cout << a << endl;
  a = a + 1;
  input[0] = a;
  cout << input << endl;
  return 0;
}
