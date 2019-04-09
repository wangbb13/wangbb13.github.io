#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1001;
typedef unsigned long long ull;

ull dp[N];

int main() {
	std::fill(dp, dp + N, 1);
	for (int i = 2; i < N; ++i) {
		int half = i / 2;
		for (int j = 1; j <= half; ++j) {
			dp[i] += dp[j];
		}
	}
	int n;
	cin >> n;
	cout << dp[n] << endl;
	return 0;
}
