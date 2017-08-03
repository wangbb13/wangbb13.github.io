#include <iostream>
#include <string>
using namespace std;

char b[27] = {0};
int map[27] = {0};

int main() {
  char ca, cb;
  int i;
  string str1, str2, str3;
  cin >> str1 >> str2 >> str3;
  if (str1.size() != str2.size()) {
    cout << "Failed" << endl;
    return 0;
  }
  for (i = 0; i < str1.size(); i++) {
    ca = (char)str1[i];
    cb = (char)str2[i];
    if (b[ca - 'A'] == 0 || b[ca - 'A'] == cb) {
      b[ca - 'A'] = cb;
    } else {
      cout << "Failed" << endl;
      return 0;
    }
  }
  for (i = 0; i < 26; i++) {
    if (b[i] == 0) {
      cout << "Failed" << endl;
      return 0;
    }
    if (map[b[i] - 'A'] == 1) {
      cout << "Failed" << endl;
      return 0;
    }
    map[b[i] - 'A'] = 1;
  }
  for (i = 0; i < str3.size(); i++) {
    ca = (char)str3[i];
    cout << b[ca - 'A'];
  }
  cout << endl;
  return 0;
}