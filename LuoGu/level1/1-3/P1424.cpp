#include <iostream>
using namespace std;

typedef unsigned long long int ull;

int main() {
	int x;
	ull n;
	cin >> x >> n;
	ull ans = (n / 7) * 250 * 5;
	int c = n % 7;
	int y = x + c;
	for (int i = x; i < y; ++i) {
		if (i == 6 || i == 7) {
			c--;
		}
	}
	ans += c * 250;
	cout << ans << endl;
	return 0;
}
