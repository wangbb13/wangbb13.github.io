/**
 * Description: power 
 * Input : n
 * Output: 2(2^..)..
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string func(int n, vector<string>& rep) {
	if (rep[n] != "") 
		return rep[n];
	int i = 1, p = 0;
	string ans = "";
	bool first = true;
	while (i <= n) {
		if (i & n) {
			string temp = "2";
			if (i != 2) 
				temp = temp + "(" + func(p, rep) + ")";
			if (first) {
				ans = temp;
				first = false;
			} else {
				ans = temp + "+" + ans;
			}
		}
		i <<= 1;
		p++;
	}
	rep[n] = ans;
	return ans;
}

int main() {
    int n;
	cin >> n;
	vector<string> rep(n + 3, "");
	rep[0] = "0";
	rep[2] = "2";
	cout << func(n, rep) << endl;
    return 0;
}

