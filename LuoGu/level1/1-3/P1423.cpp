#include <iostream>
using namespace std;

int main() {
	double a = 2.0, r = 0.98, s = 0.0, t;
	int i = 0;
	cin >> t;
	while (s < t) {
		i++;
		s += a;
		a *= r;
	}
	cout << i << endl;
	return 0;
}
