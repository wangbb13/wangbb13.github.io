#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int x = 0, y = 0, a = 0, b = 0;
	bool flag = false;
	vector<int> mode11;
	vector<int> mode21;
	while (true) {
		string str;
		getline(cin, str);
		flag = false;
		for (size_t i = 0; i < str.size(); ++i) {
			if (str[i] == 'E') {
				flag = true;
				break;
			}
			cout << ">" << str[i] << "<" << endl;
			if (str[i] == 'W') {
				x++; a++;
			} else if (str[i] == 'L') {
				y++; b++; 
			}
			if ((x >= 11 || y >= 11) && (abs(x - y) >= 2)) {
				mode11.push_back(x);
				mode11.push_back(y);
				x = y = 0;
			}
			if ((a >= 21 || b >= 21) && (abs(a - b) >= 2)) {
				mode21.push_back(a);
				mode21.push_back(b);
				a = b = 0;
			}
		}
		if (flag) 
			break;
	}
	for (size_t i = 0; i < mode11.size(); i += 2) {
		cout << mode11[i] << ":" << mode11[i + 1] << endl;
	}
	cout << x << ":" << y << endl;
	cout << endl;
	for (size_t i = 0; i < mode21.size(); i += 2) {
		cout << mode21[i] << ":" << mode21[i + 1] << endl;
	}
	cout << a << ":" << b << endl;
    return 0;
}

