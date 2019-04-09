#include <iostream>
using namespace std;

int num(int n, int x) {
	int ans = 0;
	while (n) {
		if (n % 10 == x)
			ans += 1;
		n /= 10;
	}
	return ans;
}

int main() {
	int n, x;
	cin >> n >> x;
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans += num(i, x);
	cout << ans << endl;
	return 0;
}
