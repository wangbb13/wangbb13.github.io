#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  // string input;
  // cin >> input;
  // cout << (int)(input[1] - input[0]) << endl;
  // input[0] -= 32;
  // cout << input << endl;
  // char a = input[0];
  // cout << a << endl;
  // a = a + 1;
  // input[0] = a;
  // cout << input << endl;
  vector<int> a(2, 1);
  vector<int> b(5, 2);
  vector<int> t;
  t = a;
  a = b;
  b = t;
  for (int i = 0; i < a.size(); i++) {
    cout << a[i] << " ";
  }
  cout << endl;
  for (int i = 0; i < b.size(); i++) {
    cout << b[i] << " ";
  }
  cout << endl;
  return 0;
}
