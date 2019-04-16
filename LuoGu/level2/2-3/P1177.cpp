#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

static const auto sync_off = []() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	return nullptr;
}();

inline void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void quick_sort(int *nums, int l, int r) { // [l, r]
	if (l < r) {
		int x = (rand() % (r - l)) + l;
		swap(nums + l, nums + x);
		int i = l, j = r, key = nums[l];
		while (i < j) {
			while ((i < j) && (nums[j] >= key)) {
				j--;
			}
			if (i < j) {
				nums[i] = nums[j];
				i++;
			}
			while ((i < j) && (nums[i] < key)) {
				i++;
			}
			if (i < j) {
				nums[j] = nums[i];
				j--;
			}
		}
		nums[i] = key;
		quick_sort(nums, l, i - 1);
		quick_sort(nums, i + 1, r);
	}
}

int main() {
	srand((unsigned)time(NULL));
    int n;
	cin >> n;
	int *nums = new int[n + 1];
	for (int i = 0; i < n; ++i) {
		cin >> nums[i];
	}
	// quick_sort(nums, 0, n - 1);
	sort(nums, nums + n);
	if (n > 0) {
		cout << nums[0];
	}
	for (int i = 1;i < n; ++i) {
		cout << " " << nums[i];
	}
	cout << endl;
    return 0;
}

