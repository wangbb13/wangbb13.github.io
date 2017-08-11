#include <iostream>
#include <string>
using namespace std;

string deal(string a, string b) {
  string ans = "";
  if (a.size() != 0 && b.size() != 0) {
    int len = a.size();
    int i, j;
    ans = ans + b[len-1];
    for (i = 0; i < len; i++) {
      if (a[i] == b[len-1]) {
        break;
      }
    }
    ans = ans + deal(a.substr(0, i), b.substr(0, i)) + 
          deal(a.substr(i+1, len-1-i), b.substr(i, len-1-i));
  }
  return ans;
}

int main() {
  string a, b;
  cin >> a >> b;
  cout << deal(a, b) << endl;
  return 0;
}