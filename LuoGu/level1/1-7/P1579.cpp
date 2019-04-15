#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<bool> is_prime;
vector<int> primes;

void init(int n) {
	is_prime.resize(n + 1);
	std::fill(is_prime.begin(), is_prime.end(), true);
	is_prime[0] = is_prime[1] = false;
	for (int i = 2; i <= n; ++i) {
		if (is_prime[i]) {
			primes.push_back(i);
			int x = i * 2;
			while (x <= n) {
				is_prime[x] = false;
				x += i;
			}
		}
	}
}

int main() {
	int n;
	cin >> n;
	init(n);
	for (size_t i = 0; i < primes.size(); ++i) {
		for (size_t j = i; j < primes.size(); ++j) {
			int c = n - primes[i] - primes[j];
			if (c >= 0 && c <= n && is_prime[c]) {
				cout << primes[i] << " " << primes[j] << " " << c << endl;
				return 0;
			}
		}
	}
	return 0;
}
