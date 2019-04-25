/**
 * Description: LIDS: incremental in the half subsequence and decremental in another half subsequence
 * Input : N \n the sequence of number 
 * Output: length of LIDS
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 250;
const int L = 102;
int input[L] = {0};
int lr[L] = {0};
int rl[L] = {0};
int dp[N] = {0};
int H;

int lowbit(int x) {
	return x & (-x);
}

void update(int x, int v) {
	for (int i = x; i <= H; i += lowbit(i)) {
		dp[i] = max(dp[i], v);
	}
}

int query(int x) {
	int ans = dp[x];
	for (int i = x; i > 0; i-= lowbit(i)) {
		ans = max(ans, dp[i]);
	}
	return ans;
}

int main() {
    int n, ans = 0;
	cin >> n;
	H = 0;
	for (int i = 0; i < n; ++i) {
		cin >> input[i];
		H = max(H, input[i]);
	}
	for (int i = 0; i < n; ++i) {
		int x = query(input[i]) + 1;
		lr[i] = x;
		update(input[i] + 1, x);
	}
	std::fill(dp, dp + H + 1, 0);
	for (int i = n - 1; i >= 0; --i) {
		int x = query(input[i]) + 1;
		rl[i] = x;
		update(input[i] + 1, x);
	}
	for (int i = 0; i < n; ++i) {
		ans = max(ans, lr[i] + rl[i] - 1);
	}
	cout << (n - ans) << endl;
    return 0;
}

