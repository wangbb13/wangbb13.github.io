#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
  int start, h, ans = 0, i;
  cin >> start >> h;
  ans += h;
  for (i = start; i < 2013; i++) {
    if ((i % 400 == 0) || (i % 100 != 0 && i % 4 == 0)) {
      ans += 366;
    } else {
      ans += 365;
    }
  }
  cout << ans << endl;
  return 0;
}