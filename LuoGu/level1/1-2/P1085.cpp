#include <iostream>
using namespace std;

int main() {
	int hours = 0, weekday = 0, a, b;
	for (int i = 1; i < 8; ++i) {
		cin >> a >> b;
		if (a + b > hours) {
			hours = a + b;
			weekday = i;
		}
	}
	if (hours > 8) 
		cout << weekday << endl;
	else
		cout << 0 << endl;
	return 0;
}
