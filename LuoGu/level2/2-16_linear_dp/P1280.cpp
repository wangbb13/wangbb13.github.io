/**
 * Description: Nick's task
 * Input : N K \n pi ti ... 
 * Output: maximum free time
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _task {
	int p, t;
} task;

bool compare(task& a, task& b) { 
	return ((a.p < b.p) || (a.p == b.p && a.t < b.t));
}

int main() {
    int n, k, ans;
	cin >> n >> k;
	vector<task> nums(k);
	for (int i = 0; i < k; ++i) {
		cin >> nums[i].p >> nums[i].t;
	}
	std::sort(nums.begin(), nums.end(), compare);
	vector<int> free(k, 0);
	for (int i = k - 1; i >= 0; --i) {
		int res = 0;
		int end_t = nums[i].p + nums[i].t - 1;
		int next_t = -1, j;
		for (j = i + 1; j < k; ++j) {
			if (nums[j].p > end_t) {
				next_t = nums[j].p;
				break;
			}
		}
		if (next_t == -1) {
			res += n - end_t;
		} else {
			int max_val = 0;
			for (; j < k && nums[j].p == next_t; ++j) {
				max_val = max(max_val, free[j]);
			}
			res += (next_t - end_t - 1) + max_val;
		}
		free[i] = res;
	}
	ans = 0;
	int start_t = nums[0].p;
	for (int i = 0; i < k && nums[i].p == start_t; ++i) {
		ans = max(ans, free[i]);
	}
	ans += start_t - 1;
	cout << ans << endl;
    return 0;
}

