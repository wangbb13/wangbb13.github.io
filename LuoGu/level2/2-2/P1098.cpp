#include <iostream>
#include <string>
using namespace std;

int p1, p2, p3;

bool is_letter(char ch) {
	return (ch >= 'a' && ch <= 'z');
}

bool is_number(char ch) {
	return (ch >= '0' && ch <= '9');
}

void show(char chl, char chr) {
	if (p1 == 3) {
		int nums = (int)(chr - chl - 1) * p2;
		for (int i = 0; i < nums; ++i) {
			cout << '*';
		}
		return;
	}
	char a = chl + 1, b = chr;
	int cum = 1;
	char bit = 0x20;
	if (p3 == 2) {
		a = chr - 1;
		b = chl;
		cum = -1;
	}
	if (p1 == 2 && is_letter(chl)) {
		a &= (~bit);
		b &= (~bit);
	}
	for (char i = a; i != b; i += cum) {
		for (int j = 0; j < p2; ++j) {
			cout << i;
		}
	}
}

int main() {
	cin >> p1 >> p2 >> p3;
	string str;
	cin >> str;
	for (size_t i = 0; i < str.size(); ++i) {
		if (str[i] == '-') {
			if (i > 0 && i < str.size() - 1) {
				if ( (is_letter(str[i - 1]) && is_letter(str[i + 1])) ||
					 (is_number(str[i - 1]) && is_number(str[i + 1])) ) {
					if (str[i + 1] > str[i - 1] + 1) {
						show(str[i - 1], str[i + 1]);
						continue;
					} else if (str[i + 1] == str[i - 1] + 1) {
						continue;
					}
				}
			}
		}
		cout << str[i];
	}
	cout << endl;
    return 0;
}

