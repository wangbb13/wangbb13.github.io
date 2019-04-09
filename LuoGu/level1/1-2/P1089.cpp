#include <iostream>
using namespace std;

int main() {
	int month = 0, deposit = 0, remain = 0, budget;
	for (int i = 1; i < 13; ++i) {
		cin >> budget;
		remain += 300;
		remain -= budget;
		if (remain < 0) {
			remain = 0;
			if (month == 0)
				month = i;
		} else {
			deposit += remain / 100;
			remain %= 100;
		}
	}
	if (month > 0) {
		cout << -month << endl;
	} else {
		cout << deposit * 120 + remain << endl;
	}
	return 0;
}
