#include <iostream>
#include <cmath>
using namespace std;

int nums[1005] = {0};
int vals[1005] = {0};
int righ = 0, w;

int row(int idx) {
  return ((idx - 1) / w);
}

bool legal(int idx, int brow, int off) {
  int irow = row(idx);
  return (idx >= 1 && idx <= nums[righ] && irow >= 0 && (irow == brow + off));
}

int cacu(int idx, int b) {
  int ans = -1;
  int val = vals[b];
  int cro = row(idx);
  int j, a;
  if (legal(idx - w - 1, cro, -1)) {
    j = b;
    a = idx - w - 1;
    while (!((j == 0 && nums[j] >= a) || (nums[j] >= a && nums[j - 1] < a))) j--;
    ans = max(ans, abs(val - vals[j]));
  }
  if (legal(idx - w, cro, -1)) {
    j = b;
    a = idx - w;
    while (!((j == 0 && nums[j] >= a) || (nums[j] >= a && nums[j - 1] < a))) j--;
    ans = max(ans, abs(val - vals[j]));
  }
  if (legal(idx - w + 1, cro, -1)) {
    j = b;
    a = idx - w + 1;
    while (!((j == 0 && nums[j] >= a) || (nums[j] >= a && nums[j - 1] < a))) j--;
    ans = max(ans, abs(val - vals[j]));
  }
  if (legal(idx - 1, cro, 0)) {
    j = b;
    a = idx - 1;
    while (!((j == 0 && nums[j] >= a) || (nums[j] >= a && nums[j - 1] < a))) j--;
    ans = max(ans, abs(val - vals[j]));
  }
  if (legal(idx + 1, cro, 0)) {
    j = b;
    a = idx + 1;
    while (!((j == 0 && nums[j] >= a) || (nums[j] >= a && nums[j - 1] < a))) j++;
    ans = max(ans, abs(val - vals[j]));
  }
  if (legal(idx + w - 1, cro, 1)) {
    j = b;
    a = idx + w - 1;
    while (!((j == 0 && nums[j] >= a) || (nums[j] >= a && nums[j - 1] < a))) j++;
    ans = max(ans, abs(val - vals[j]));
  }
  if (legal(idx + w, cro, 1)) {
    j = b;
    a = idx + w;
    while (!((j == 0 && nums[j] >= a) || (nums[j] >= a && nums[j - 1] < a))) j++;
    ans = max(ans, abs(val - vals[j]));
  }
  if (legal(idx + w + 1, cro, 1)) {
    j = b;
    a = idx + w + 1;
    while (!((j == 0 && nums[j] >= a) || (nums[j] >= a && nums[j - 1] < a))) j++;
    ans = max(ans, abs(val - vals[j]));
  }
  return ans;
}

int main() {
  int num, val, idx;
  while ((cin >> w) && w > 0) {
    cin >> val >> num;
    if (num == 0 && val == 0) {
      cout << w << endl << val << " " << num << endl;
      continue;
    }
    nums[righ] = num;
    vals[righ] = val;
    while ((cin >> val >> num) && (val != 0 && num != 0)) {
      nums[++righ] = num + nums[righ - 1];
      vals[righ]   = val;
    }
    cout << w << endl;
    num = 1;
    val = cacu(1, 0);
    idx = 0;
    for (int i = 2; i <= nums[righ]; i++) {
      if (i > nums[idx]) idx++;
      if (i % w == 1) {
        int th = 0;
        if (idx > 0) {
          th = nums[idx - 1];
        }
        if (i - th > w) {
          int x = nums[idx] - i + 1;
          x = x / w - 1;
          if (x > 0) {
            if (val == 0) {
              num += x * w;
            } else {
              cout << val << " " << num << endl;
              val = 0;
              num = x * w;
            }
            i += x * w;
            i--;
            continue;
          }
        }
      }
      int j = cacu(i, idx);
      if (j == val) {
        num ++;
      } else {
        cout << val << " " << num << endl;
        val = j;
        num = 1;
      }
    }
    cout << val << " " << num << endl;
    cout << 0 << " " << 0 << endl;
    righ = 0;
  }
  cout << 0 << endl;
  return 0;
}