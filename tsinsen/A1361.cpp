#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
  int n, i, m, ans = 0;
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> m;
    ans += (m > 1000) * (m - 1000);
  }
  cout << ans << endl;
  return 0;
}