/*
 * Problem: max sum of a sub-sequence
 * Input  : test cases
 *          a0, a1, ...
 *          ...
 * Output : max_sum, start_pos, end_pos
 */
#include <iostream>
#include <vector>
using namespace std;

void deal(vector<int>& nums) {
  int i, t, s, ta, a, b, len = nums.size();
  s = nums[0];
  t = ta = a = b = 0;
  for (i = 0; i < len; i++) {
    t += nums[i];
    if (t > s) {
      s = t;
      b = i;
      a = ta;
    }
    if (t < 0) {
      t = 0;
      ta = i + 1;
    }
  }
  cout << s << " " << (++a) << " " << (++b) << endl;
}

int main() {
  int t, l, k = 1;
  cin >> t;
  while (t--) {
    cin >> l;
    vector<int> nums(l);
    for (int i = 0; i < l; i++) {
      cin >> nums[i];
    }
    cout << "Case " << k++ << ":" << endl;
    deal(nums);
    if (t) { cout << endl; }
  }
  return 0;
}