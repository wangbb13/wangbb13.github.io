#include <iostream>
#include <vector>
using namespace std;

static const auto io_sync_off = []() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	return nullptr;
}();

typedef struct _m_pair {
	int no, score;
} m_pair;

bool compare(m_pair a, m_pair b) { // put "a" in the front position ? 
	return ((a.score > b.score) || (a.score == b.score && a.no < b.no));
}

void quick_sort(vector<m_pair>& nums, int l, int r) { // [l, r]
	if (l < r) {
		int i = l, j = r;
		m_pair key = nums[l];
		while (i < j) {
			while ((i < j) && (!compare(nums[j], key))) {
				j--;
			}
			if (i < j) {
				nums[i] = nums[j];
				i++;
			}
			while ((i < j) && (compare(nums[i], key))) {
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
    int n, m;
	cin >> n >> m;
	vector<m_pair> nums(n);
	for (int i = 0; i < n; ++i) {
		cin >> nums[i].no >> nums[i].score;
	}
	quick_sort(nums, 0, n - 1);
	m = m + (m >> 1) - 1;
	cout << nums[m].score << " ";
	while (m + 1 < n && (nums[m].score == nums[m + 1].score)) {
		m++;
	}
	cout << ++m << endl;
	for (int i = 0; i < m; ++i) {
		cout << nums[i].no << " " << nums[i].score << endl;
	}
    return 0;
}

