#include <iostream>
using namespace std;

int main() {
	int k, i = 0;
	cin >> k;
	double s = 0.0;
	while (s <= k) {
		s += 1.0 / (++i);
	}
	cout << i << endl;
	return 0;
}
