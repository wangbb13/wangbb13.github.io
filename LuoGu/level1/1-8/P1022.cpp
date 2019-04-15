#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
	string str;
	getline(cin, str);
	const char *p = str.c_str();
	int a = 0, b = 0, number = 0;
	int *pab;
	char x;
	bool plus = true, d_num = false, equal = false, letter = false;
	while (*p != 0) {
		if (*p >= 'a' && *p <= 'z') {
			x = *p;
			if (!d_num) {
				number = 1;
			}
			letter = true;
			d_num = false;
		} else if (*p >= '0' && *p <= '9') {
			if (d_num) {
				number = number * 10 + (int)(*p - '0');
			} else {
				d_num = true;
				number = (int)(*p - '0');
			}
		} else {
			if (letter) {
				pab = &a;
			} else {
				pab = &b;
			}
			if (plus ^ equal) {
				*pab += number;
			} else {
				*pab -= number;
			}
			d_num = false;
			letter = false;
			number = 0;
		}
		if (*p == '+') {
			plus = true;
		} else if (*p == '-') {
			plus = false;
		} else if (*p == '=') {
			equal = true;
			plus = true;
		}
		p++;
	}
	if (letter) {
		pab = &a;
	} else {
		pab = &b;
	}
	if (plus) {
		*pab -= number;
	} else {
		*pab += number;
	}
	double ans = (double)(-b) / (double)(a);
	if (ans == 0.0) {
		ans = 0.0;
	}
	cout << x << "=" << std::fixed << std::setprecision(3) << ans << endl;
	return 0;
}
