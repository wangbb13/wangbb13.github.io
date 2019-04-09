#include <iostream>
using namespace std;

int main() {
	char ch[100] = {0};
	int l = 0, j = 0, r;
	cin >> ch;
	while (j < 100 && (ch[j] >= '0' && ch[j] <= '9')) j++;
	r = j - 1;
	while (l < j && ch[l] == '0') l++;
	while (r >= 0 && ch[r] == '0') r--;
	for (int i = r; i >= l; --i) {
		cout << ch[i];
	}
	if (l > r) {
		cout << 0;
	}
	if (ch[j] == 0) {
		cout << endl;
	} else if (ch[j] == '%') {
		cout << '%' << endl;
	} else {
		cout << ch[j];
		l = ++j;
		while (j < 100 && (ch[j] >= '0' && ch[j] <= '9')) j++;
		r = j - 1;
		while (l < j && ch[l] == '0') l++;
		while (r >= 0 && ch[r] == '0') r--;
		for (int i = r; i >= l; --i) {
			cout << ch[i];
		}
		if (l > r) {
			cout << 0;
		}
		cout << endl;
	}
	return 0;
}
