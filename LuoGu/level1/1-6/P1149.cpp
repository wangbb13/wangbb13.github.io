#include <iostream>
using namespace std;

int list[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int need(int n) {
	int ans = 0;
	do {
		ans += list[n % 10];
		n /= 10;
	} while (n > 0);
	return ans;
}

int main() {
	int n, ans = 0;
	cin >> n;
	n -= 4;
	for (int i = 0; i < 1001; ++i) {
		if (need(i) * 2 + need(i * 2) == n)
			ans++;
		for (int j = i + 1; j < 1001; ++j) {
			if (need(i) + need(j) + need(i + j) == n) 
				ans += 2;
		}
	}
	cout << ans << endl;
	return 0;
}
