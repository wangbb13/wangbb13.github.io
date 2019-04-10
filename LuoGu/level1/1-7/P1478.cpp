#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& nums, int l, int r) { // [l, r)
	int k = nums[l], i = l, j;
	for (j = l + 1; j < r; ++j) {
		if (nums[j] < k) {
			i++;
			int temp = nums[i];
			nums[i] = nums[j];
			nums[j] = temp;
		}
	}
	int temp = nums[i];
	nums[i] = nums[l];
	nums[l] = temp;
	return i;
}

void quick_sort(vector<int>& nums, int l, int r) { // [l, r)
	if (l < r) {
		int p = partition(nums, l, r);
		quick_sort(nums, l, p);
		quick_sort(nums, p + 1, r);
	}
}

int main() {
	int n, s, a, b, x, y, len, ans;
	cin >> n >> s;
	vector<int> nums(n);
	cin >> a >> b;
	a += b;
	len = 0;
	for (int i = 0; i < n; ++i) {
		cin >> x >> y;
		if (x <= a) {
			nums[len++] = y;
		}
	}
	quick_sort(nums, 0, len);
	ans = 0; y = 0;
	for (int i = 0; i < len; ++i) {
		y += nums[i];
		if (y > s) {
			break;
		} else {
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
