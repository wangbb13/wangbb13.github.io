/**
 * Description: permutation
 * Input : N \n additions M \n a permutation
 * Output: the next M permutation
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
using namespace std;

void next(vector<int>& nums) {
	// 1 2 5 4 3
	size_t last = nums.size() - 1;
	int l, r = last;
	while (last > 0 && nums[last] < nums[last - 1]) last--;
	if (last == 0) return;
	int replace = last;
	while (replace <= r && nums[replace] > nums[last - 1]) replace++;
	replace--;
	int temp = nums[last - 1];
	nums[last - 1] = nums[replace];
	nums[replace] = temp;
	l = last;
	while (l < r) {
		temp = nums[l];
		nums[l] = nums[r];
		nums[r] = temp;
		l++; r--;
	}
}

int main() {
    int N, M;
	cin >> N >> M;
	vector<int> nums(N);
	for (int i = 0; i < N; ++i) {
		cin >> nums[i];
	}
	for (int i = 0; i < M; ++i) {
		next(nums);
	}
	cout << nums[0];
	for (int i = 1; i < N; ++i) {
		cout << " " << nums[i];
	}
	cout << endl;
    return 0;
}

