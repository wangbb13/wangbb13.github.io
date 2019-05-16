/**
 * Description: guard of honor 
 * Input : N (N * N square)
 * Output: the maximum people we can see (at the corner)
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

const int N = 40001;

bool prime[N];

void init(int n) {
	for (int i = 0; i <= n; ++i) {
		prime[i] = true;
	}
}

void gen(vector<int> &factors, unordered_set<int> &nums, int cn, int k, int p) {
	if (cn == k) {
		nums.insert(p);
		return;
	}
	int len = factors.size();
	for (int i = cn; i < len; ++i) {
		int temp = factors[i];
		factors[i] = factors[cn];
		factors[cn] = temp;
		gen(factors, nums, cn + 1, k, p * factors[cn]);
		temp = factors[i];
		factors[i] = factors[cn];
		factors[cn] = temp;
	}
}

int calc(int n) {	// including n
	init(n);
	int ans = n - 1;
	vector< vector<int> > factor(n + 1);
	prime[0] = prime[1] = false;
	for (int i = 2; i <= n; ++i) {
		int remain = n - i;
		if (prime[i]) {
			int j = i * 2;
			while (j <= n) {
				prime[j] = false;
				remain--;
				factor[j].push_back(i);
				j += i;
			}
		} else {
			int size = factor[i].size();
			bool flag = true;
			for (int x = 0; x < size; ++x) {
				unordered_set<int> nums;
				gen(factor[i], nums, 0, x + 1, 1);
				int sum = 0;
				for (auto & e : nums) {
					sum += (n / e - i / e);
				}
				if (flag) remain -= sum;
				else remain += sum;
				flag = !flag;
			}
		}
		// cout << i << ":" << remain << endl;
		ans += remain;
	}
	return ans;
}

int gcd(int a, int b) {
	while (a > 0 && b > 0) {
		if (a < b) {
			int temp = a;
			a = b;
			b = temp;
		}
		a -= b;
	}
	return a + b;
}

int main() {
    int n;
	cin >> n;
	if (n == 1) {
		cout << 0 << endl;
		return 0;
	}
	cout << (3 + 2 * calc(n - 1)) << endl;
	// int ans = 0;
	// for (int i = 1; i < n; ++i) {
	// 	int remain = 0;
	// 	for (int j = i + 1; j < n; ++j) {
	// 		if (gcd(i, j) == 1) remain++;
	// 	}
	// 	// cout << i << ":" << remain << endl;
	// 	ans += remain;
	// }
	// cout << (3 + 2 * ans) << endl;
    return 0;
}

