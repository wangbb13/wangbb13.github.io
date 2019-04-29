/**
 * Description: concat numbers 
 * Input : n \n ...
 * Output: maximum concated number
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool compare(int a, int b) {
	vector<int> al;
	vector<int> bl;
	do {
		al.push_back(a % 10);
		a /= 10;
	} while (a > 0);
	do {
		bl.push_back(b % 10);
		b /= 10;
	} while (b > 0);
	size_t as = al.size();
	size_t bs = bl.size();
	for (int i = 0; i < as; ++i) {
		bl.push_back(al[i]);
	}
	for (int i = 0; i < bs; ++i) {
		al.push_back(bl[i]);
	}
	for (int i = as + bs - 1; i >= 0; --i) {
		if (bl[i] > al[i]) {
			return true;
		} else if (bl[i] < al[i]) {
			return false;
		}
	}
	return false;
}

int main() {
    int n;
	cin >> n;
	vector<int> nums(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> nums[i];
	}
	sort(nums.begin(), nums.end(), compare);
	for (int i = 0; i < n; ++i) {
		cout << nums[i];
	}
	cout << endl;
    return 0;
}

