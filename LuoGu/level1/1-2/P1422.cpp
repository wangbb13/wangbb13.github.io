#include <iostream>
#include <iomanip>
using namespace std;

const double cost0 = 0.4463;
const double cost1 = 0.4663;
const double cost2 = 0.5663;

int main() {
	int a;
	cin >> a;
	double ans = 0.0;
	if (a < 151) {
		ans = a * cost0;
	} else if (a < 401) {
		ans = 150 * cost0 + (a - 150) * cost1;
	} else {
		ans = 150 * cost0 + 250 * cost1 + (a - 400) * cost2;
	}
	cout << std::fixed << std::setprecision(1) << ans << endl;
	return 0;
}
