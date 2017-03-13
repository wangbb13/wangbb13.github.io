/*
 二叉树的最小表示方法：
 tree = ((...)(...))
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string min_pre(string str) {
	vector<string> box;
	int i, j = 0, equal = 0;
	string ret = "";
	for (i = 0; i < str.size(); i++) {
		if (str[i] == '0') {
			equal++;
		} else {
			equal--;
		}
		if (equal == 0) {
			if ((i - j + 1) > 2) {
				box.push_back("0" + min_pre(str.substr(j+1, i-1-j)) + "1");
			} else {
				box.push_back("01");
			}
			j = i+1;
		}
	}
	sort(box.begin(), box.end());
	for (i = 0; i < box.size(); i++) {
		ret += box[i];
	}
	return ret;
}

int main() {
	int n;
	string str0, str1;
	cin >> n;
	while (n--) {
		cin >> str0 >> str1;
		if (min_pre(str0) == min_pre(str1)) {
			cout << "same" << endl;
		} else {
			cout << "different" << endl;
		}
	}
	return 0;
}