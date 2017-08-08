#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/*
 * 最长公共子序列
 * dp数组下标从1开始，以减少复杂判断
 * 在求解子序列内容时，(i,j)与(i-1,j-1)的关系最后判断
 */

bool comp(int a, int b) {
  return a > b;
}

vector<int> maxDescSub(vector<int> nums) {
  vector<int> ans;
  if (nums.size() < 2) {
    ans.push_back(nums.size());
    return ans;
  }
  vector<int> cp(nums.begin(), nums.end());
  sort(cp.begin(), cp.end(), comp);
  int len = nums.size();
  vector< vector<int> > dp(len+1, vector<int>(len+1, 0));
  int i, j;
  for (i = 1; i <= len; i++) {
    for (j = 1; j <= len; j++) {
      if (cp[i-1] == nums[j-1]) {
        dp[i][j] = 1 + dp[i-1][j-1];
      } else {
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      }
    }
  }
  ans.push_back(dp[len][len]);
  vector<bool> info(len, true);
  i = len; j = len;
  while (i > 0 && j > 0) {
    if (dp[i][j] == dp[i][j-1]) {
      j--;
    } else if (dp[i][j] == dp[i-1][j]) {
      i--;
    } else if (dp[i][j] == dp[i-1][j-1] + 1) {
      i--; j--;
      info[j] = false;
    }
  }
  for (i = 0; i < len; i++) {
    if (info[i]) {
      ans.push_back(nums[i]);
    }
  }
  return ans;
}

int main() {
  int n, i = 0, j;
  char ch;
  vector<int> nums, ans;
  while (cin >> n) {
    nums.push_back(n);
    ch = cin.get();
    if (ch == '\n') {
      break;
    }
  }
  ans = maxDescSub(nums);
  j = ans[0];
  i++;
  ans.erase(ans.begin());
  while (ans.size() > 0) {
    ans = maxDescSub(ans);
    i++;
    ans.erase(ans.begin());
  }
  cout << j << endl << i << endl;
  return 0;
}