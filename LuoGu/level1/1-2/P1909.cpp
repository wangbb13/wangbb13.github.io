#include <iostream>
using namespace std;

int main() {
	int need, num, price, cost = 0x1fffffff, a;
	cin >> need;
	for (int i = 0; i < 3; ++i) {
		cin >> num >> price;
		a = (need / num + (need % num != 0)) * price;
		if (a < cost)
			cost = a;
	}
	cout << cost << endl;
	return 0;
}
