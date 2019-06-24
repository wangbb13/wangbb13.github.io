/**
 * Description: high resolution A - B
 * Input : A, B
 * Output: A - B
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int Bits = 10003;

void str2num(string& str, vector<int>& num) {
	int i = str.size() - 1;
	int j = Bits - 1;
	while (i >= 0) {
		char ch = str[i];
		num[j] = (int)(ch - '0');
		i--; j--;
	}
}

bool m_greater(vector<int>& num1, vector<int>& num2) {
	for (int i = 0; i < Bits; ++i) {
		if (num1[i] > num2[i]) 
			return true;
		else if (num1[i] < num2[i]) 
			return false;
	}
}

bool is_zero(vector<int>& num) {
	for (int i = 0; i < Bits; ++i) {
		if (num[i] != 0) return false;
	}
	return true;
}

void minux(vector<int>& num1, vector<int>& num2, vector<int>& ans) {
	for (int i = Bits - 1; i >= 0; --i) {
		if (num1[i] >= num2[i]) {
			ans[i] = num1[i] - num2[i];
		} else {
			ans[i] = 10 + num1[i] - num2[i];
			int j = i - 1;
			while (j >= 0 && num1[j] == 0) j--;
			num1[j++]--;
			while (j < i) num1[j++] = 9;
		}
	}
}

void add(vector<int>& num1, vector<int>& num2, vector<int>& ans) {
	int remain = 0, sum;
	for (int i = Bits - 1; i >= 0; --i) {
		sum = remain + num1[i] + num2[i];
		ans[i] = sum % 10;
		remain = sum / 10;
	}
}

void show(vector<int>& num) {
	int i = 0;
	while (i < Bits && num[i] == 0) i++;
	for (; i < Bits; ++i) 
		cout << num[i];
	cout << endl;
}

int main() {
    string str1, str2;
	bool a_minux = false;
	bool b_minux = false;
	cin >> str1 >> str2;
	vector<int> num1(Bits, 0);
	vector<int> num2(Bits, 0);
	vector<int> ans(Bits, 0);
	if (str1[0] == '-') {
		a_minux = true;
		str1 = str1.substr(1);
	}
	if (str2[0] == '-') {
		b_minux = true;
		str2 = str2.substr(1);
	}
	str2num(str1, num1);
	str2num(str2, num2);
	if (!m_greater(num1, num2)) {
		vector<int> temp(Bits);
		std::copy(num2.begin(), num2.end(), temp.begin());
		std::copy(num1.begin(), num1.end(), num2.begin());
		std::copy(temp.begin(), temp.end(), num1.begin());
		a_minux = !a_minux;
		b_minux = !b_minux;
	}
	if (a_minux && !b_minux) {
		add(num1, num2, ans);
		if (!is_zero(ans)) {
			cout << "-";
			show(ans);
		} else {
			cout << 0 << endl;
		}
	} else if (a_minux && b_minux) {
		minux(num1, num2, ans);
		if (!is_zero(ans)) {
			cout << "-";
			show(ans);
		} else {
			cout << 0 << endl;
		}
	} else if (!a_minux && b_minux) {
		add(num1, num2, ans);
		if (is_zero(ans)) cout << 0 << endl;
		else show(ans);
	} else {
		minux(num1, num2, ans);
		if (is_zero(ans)) cout << 0 << endl;
		else show(ans);
	}
    return 0;
}

