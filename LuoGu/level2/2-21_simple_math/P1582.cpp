/**
 * Description: ... 
 * Input : 
 * Output: 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
using namespace std;

int nums(int n) {
	int ans = 0;
	while (n) {
		ans++;
		n &= (n - 1);
	}
	return ans;
}

int lowbit(int n) {
	return n & (-n);
}

int main() {
    int n, k, lb, ans = 0;
	cin >> n >> k;
	while (k < nums(n)) {
		lb = lowbit(n);
		ans += lb;
		n += lb;
	}
	cout << ans << endl;
    return 0;
}

