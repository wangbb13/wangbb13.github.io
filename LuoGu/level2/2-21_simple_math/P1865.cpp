/**
 * Description: simple ... 
 * Input : 
 * Output: 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
using namespace std;

void calcPrime(vector<int>& nums, int& lp, int r) {
	size_t len = nums.size();
	while ((lp <= r) && (lp < len)) {
		for (size_t i = lp * 2; i < len; i += lp) {
			nums[i] = 0;
		}
		size_t i = lp + 1;
		for (; (i < len) && (nums[i] == 0); ++i) {
			nums[i] = nums[i - 1];
		}
		lp = i;
		nums[lp] = nums[lp - 1] + 1;
	}
}

int main() {
    int n, m, l, r, cp = 2;
	cin >> n >> m;
	vector< int > prime(m + 1, 1);
	prime[0] = 0;
	if (m > 0) 
		prime[1] = 0;
	for (int i = 0; i < n; ++i) {
		cin >> l >> r;
		if ((l > 0 && l <= m) && (r > 0 && r <= m)) {
			if (r > cp) 
				calcPrime(prime, cp, r);
			cout << prime[r] - prime[l - 1] << endl;
		} else {
			cout << "Crossing the line" << endl;
		}
	}
    return 0;
}

