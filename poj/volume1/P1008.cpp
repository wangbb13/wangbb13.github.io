#include <iostream>
#include <string>
using namespace std;

string h_month[] = {"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"};
string t_month[] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};

int find(string str) {
  int i;
  for (i = 0; i < 19; i++) {
    if (str == h_month[i]) {
      break;
    }
  }
  return i;
}

int main() {
  int n, d, y, days;
  string m;
  char ch;
  cin >> n;
  cout << n << endl;
  while (n--) {
    cin >> d >> ch >> m >> y;
    days = y * 365 + (find(m) * 20) + d;
    cout << (days % 13 + 1) << " " << t_month[days % 20] << " " << (days / 260) << endl;
  }
  return 0;
}