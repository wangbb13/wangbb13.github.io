#include <iostream>
#include <vector>
using namespace std;

vector<int> primes;
int cur_prime = 2;
int prime_size = 0;

bool is_prime(int n) {
	while (primes[n] < 0) {
		int i = cur_prime * 2;
		while (i < prime_size) {
			primes[i] = 0;
			i += cur_prime;
		}
		do {
			cur_prime++;
		} while (primes[cur_prime] == 0);
		primes[cur_prime] = 1;
	}
	return (primes[n] == 1);
}

void recursion(vector<int>& nums, int start, int count, int sum, int& ans) {
	if (count == 0) {
		if (is_prime(sum)) 
			ans++;
		return;
	}
	for (int i = start; i < nums.size(); ++i) {
		sum += nums[i];
		count--;
		recursion(nums, i + 1, count, sum, ans);
		count++;
		sum -= nums[i];
	}
}

int main() {
	int n, k, sum = 0, ans = 0;
	cin >> n >> k;
	vector<int> nums(n);
	for (int i = 0; i < n; ++i) {
		cin >> nums[i];
		sum += nums[i];
	}
	primes.resize(sum + 1);
	prime_size = sum + 1;
	std::fill(primes.begin(), primes.end(), -1);
	primes[0] = primes[1] = 0;
	primes[2] = 1;
	recursion(nums, 0, k, 0, ans);
	cout << ans << endl;
	return 0;
}
