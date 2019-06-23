/**
 * Description: A + B
 * Input : 
 * Output: 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int Bits = 1000;

void show(vector<int>& num) {
	size_t i = 0;
	while (i < Bits && num[i] == 0) i++;
	if (i == Bits) {
		cout << 0 << endl;
	} else {
		for (; i < Bits; ++i) 
			cout << num[i];
		cout << endl;
	}
}

void add(vector<int>& num1, vector<int>& num2, vector<int>& ans) {
	int sum = 0, remain = 0;
	for (int i = Bits - 1; i >= 0; --i) {
		sum = num1[i] + num2[i] + remain;
		ans[i] = sum % 10;
		remain = sum / 10;
	}
}

void toNum(string str, vector<int>& num) {
	size_t len = str.size();
	if (len == 0) return;
	for (size_t i = 0, j = Bits - len; i < len; ++i, ++j) {
		num[j] = (int)(str[i] - '0');
	}
}

int main() {
    string str1, str2;
	cin >> str1 >> str2;
	vector<int> num1(Bits, 0);
	vector<int> num2(Bits, 0);
	vector<int> ans(Bits, 0);
	toNum(str1, num1);
	toNum(str2, num2);
	add(num1, num2, ans);
	show(ans);
    return 0;
}

