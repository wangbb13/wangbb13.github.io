/**
 * Description: merge fruits
 * Input : n \n numbers
 * Output: minimum cost
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
using namespace std;

void min_heap(vector<int>& nums, int size, int i) {
	int l = i * 2;
	int r = l + 1;
	int min_i = i;
	if (l <= size && nums[l] < nums[min_i]) 
		min_i = l;
	if (r <= size && nums[r] < nums[min_i]) 
		min_i = r;
	if (min_i != i) {
		int temp = nums[i];
		nums[i] = nums[min_i];
		nums[min_i] = temp;
		min_heap(nums, size, min_i);
	}
}

int main() {
    int n, ans = 0, a;
	cin >> n;
	vector<int> nums(n + 1);
	for (int i = 0; i < n; ++i) {
		cin >> nums[i + 1];
	}
	for (int i = n / 2; i > 0; --i) {
		min_heap(nums, n, i);
	}
	int temp, size = n;
	for (int i = 0; i < size - 1; ++i) {
		a = nums[1];
		temp = nums[1];
		nums[1] = nums[n];
		nums[n] = temp;
		min_heap(nums, --n, 1);
		ans += a + nums[1];
		nums[1] += a;
		min_heap(nums, n, 1);
	}
	cout << ans << endl;
    return 0;
}

