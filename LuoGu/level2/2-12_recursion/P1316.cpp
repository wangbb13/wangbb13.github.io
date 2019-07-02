/**
 * Description: toss bottle cap 
 * Input : A B \n A numbers 
 * Output: maximum ( minimum dist )
 * Time/Space Limit: 1s/128MB
 * PS: Binary Search Answer 
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool check(vector<int>& nums, int step, int m) {
	int target = nums[0] + step;
	int count = 1;
	for (size_t i = 0; i < nums.size(); ++i) {
		if (nums[i] >= target) {
			count++;
			if (count >= m) return true;
			target = nums[i] + step;
		}
	}
	return (count >= m);
}

int main() {
    int a, b;
	cin >> a >> b;
	vector<int> nums(a);
	for (int i = 0; i < a; ++i) 
		cin >> nums[i];
	sort(nums.begin(), nums.end());
	int l = 0, r = nums[a - 1] - nums[0];
	while (l < r) {
		int mid = (l + r) / 2;
		if (!check(nums, mid, b))
			r = mid;
		else
			l = mid + 1;
	}
	cout << l - 1 << endl;
    return 0;
}

