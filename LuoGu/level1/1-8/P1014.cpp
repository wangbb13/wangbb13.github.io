#include <iostream>
using namespace std;

int find(int n) {
	int l = 0, r = 10000;
	while (l < r) {
		int mid = (l + r) / 2;
		if (mid * (mid + 1) > n) {
			r = mid;
		} else {
			l = mid + 1;
		}
	}
	return l - 1;
}

int main() {
	int n;
	cin >> n;
	int x = find(n * 2);
	int remain;
	if (n * 2 == x * (x + 1)) {
		remain = n - (x - 1) * x / 2;
	} else {
		remain = n - (x + 1) * x / 2;
		x++;
	}
	if (x % 2 == 0) {
		cout << remain << "/" << x + 1 - remain << endl;
	} else {
		cout << x + 1 - remain << "/" << remain << endl;
	}
	return 0;
}
