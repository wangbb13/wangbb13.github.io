/**
 * Description: A * B, high precision 
 * Input : A, B (10 ^ 2000)
 * Output: A * B
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int Bits = 5000;

void show(vector<int>& nums) {
	int i = 0;
	while (i < Bits && nums[i] == 0) i++;
	for (; i < Bits; ++i) 
		cout << nums[i];
	cout << endl;
}

bool is_zero(vector<int>& nums) {
	for (int i = 0; i < Bits; ++i) {
		if (nums[i] != 0) return false;
	}
	return true;
}

void str2num(const string& str, vector<int>& nums) {
	int i = str.size() - 1, j = Bits - 1;
	while (i >= 0) {
		nums[j] = (int)(str[i] - '0');
		i--, j--;
	}
}

void hp_add(vector<int>& A, vector<int>& B) {	// B = B + A
	int remain = 0, sum = 0;
	int i = Bits - 1;
	while (i >= 0) {
		sum = A[i] + B[i] + remain;
		remain = sum / 10;
		B[i] = sum % 10;
		i--;
	}
}

int highest_bit(vector<int>& nums) {
	int ans = 0;
	while (ans < Bits && nums[ans] == 0) ans++;
	return ans;
}

void multiply(vector<int>& A, vector<int>& B, vector<int>& C) {
	int bi = Bits - 1, bli = highest_bit(B);
	int ali = highest_bit(A);
	int remain = 0;
	while (bi >= bli) {
		vector<int> temp(Bits);
		int mul = B[bi];
		int ti = bi;
		remain = 0;
		for (int ai = Bits - 1; ai >= ali; --ai) {
			int prod = mul * A[ai] + remain;
			remain = prod / 10;
			temp[ti] = prod % 10;
			ti--;
		}
		if (remain > 0) temp[ti] = remain;
		hp_add(temp, C);
		bi--;
	}
}

int main() {
    string str1, str2;
	cin >> str1 >> str2;
	bool a_minus = false;
	bool b_minus = false;
	if (str1.size() > 0 && str1[0] == '-') { 
		a_minus = true;
		str1 = str1.substr(1);
	}
	if (str2.size() > 0 && str2[0] == '-') {
		b_minus = true;
		str2 = str2.substr(1);
	}
	vector<int> A(Bits);
	vector<int> B(Bits);
	str2num(str1, A);
	str2num(str2, B);
	vector<int> C(Bits);
	multiply(A, B, C);
	if (is_zero(C)) {
		cout << 0 << endl;
		return 0;
	}
	if (a_minus ^ b_minus) cout << '-';
	show(C);
    return 0;
}

