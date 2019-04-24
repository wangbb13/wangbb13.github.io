/**
 * Description: missiles interceptors, equals to longest incremental subsequence
 * Input : several (<= 100,000) integers ni (0 < ni <= 50,000)
 * Output: 1. the length of LIS; 2. the number of disjoint LIS
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 100002;
int H;

int height[N] = {0};
int dp[N] = {0};

inline int lowbit(int x) {
	return x & (-x);
}

void update_1(int x, int v) {
	for (int i = x; i <= H; i += lowbit(i)) {
		dp[i] = max(dp[i], v);
	}
}

int query_1(int x) {
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		ans = max(ans, dp[i]);
	}
	return ans;
}

void update_2(int x, int v) {
	for (int i = x; i > 0; i-= lowbit(i)) {
		dp[i] = max(dp[i], v);
	}
}

int query_2(int x) {
	int ans = 0;
	for (int i = x; i <= H; i += lowbit(i)) {
		ans = max(ans, dp[i]);
	}
	return ans;
}

int main() {
    int h = 0, length = 0, ans = 0, cnt = 0;
	H = 0;
	while (scanf("%d", &h) != EOF) {
		height[length++] = h;
		H = max(H, h);
	}
	std::fill(dp, dp + H + 1, 0);
	// longest monotonous not-incremental subsequence
	for (int i = 0; i < length; ++i) {
		int x = query_2(height[i]) + 1;
		ans = max(ans, x);
		// update_2 dp[j] where j <= height[i]
		update_2(height[i], x);
	}
	std::fill(dp, dp + H + 1, 0);
	// longest monotonous incremental subsequence
	for (int i = 0; i < length; ++i) {
		// query_1 dp[height[i]] to update ans
		int x = query_1(height[i]) + 1;
		cnt = max(cnt, x);
		// update_1 dp[j] where j > height[i] 
		update_1(height[i] + 1, x);
	}
	cout << ans << endl << cnt << endl;
    return 0;
}

