/*
 * Problem: find the most popular color
 * Input  : test cases
 *        : c0, c1, c2, ... 
 *        ....
 * Output : c_x
 *          c_y
 *          ...
 */
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
  int n, i, mx;
  string str, ans;
  unordered_map<string, int> my_map;
  while ((cin >> n) && n) {
    my_map.clear();
    mx = 0;
    for (i = 0; i < n; i++) {
      cin >> str;
      if (my_map.count(str) == 0) {
        my_map[str] = 1;
      } else {
        my_map[str] += 1;
      }
      if (my_map[str] > mx) {
        mx = my_map[str];
        ans = str;
      }
    }
    cout << ans << endl;
  }
  return 0;
}