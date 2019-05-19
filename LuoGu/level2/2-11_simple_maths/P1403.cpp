/**
 * Description: the study of divisor
 * Input : n
 * Output: sigma_i=1_n f(n), f(x): the number of divisors of x
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
using namespace std;

int main() {
    int n, ans = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		ans += n / i;
	}
	cout << ans << endl;
    return 0;
}

