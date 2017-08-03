#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
  int n, i, j;
  int list[1003];
  int ans = 0, sum = 0, avg = 0, delta;
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> list[i];
    sum += list[i];
  }
  avg = sum / n;
  for (i = 0; i < n; i++) {
    if (list[i] > avg) {
      delta = list[i] - avg;
      list[i+1] += delta;
      ans += delta;
    } else if (list[i] < avg) {
      delta = avg - list[i];
      for (j = i+1; j < n && delta > 0; j++) {
        if (list[j] > avg) {
          int a = min((list[j] - avg), delta);
          ans += a * (j-i);
          list[j] -= a;
          delta -= a;
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}