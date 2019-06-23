/**
 * Description: suffix expression
 * Input : string
 * Output: value
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

int str2num(string str) {
	istringstream iss(str);
	int ans;
	iss >> ans;
	return ans;
}

int main() {
    string exp;
	cin >> exp;
	int num = 0;
	size_t i = 0, j = 0;
	stack<int> left;
	queue<string> right;
	for (; j < exp.size(); ++j) {
		if (exp[j] == '+' || exp[j] == '-' || exp[j] == '*' || exp[j] == '/') {
			right.push(exp.substr(j, 1));
			i = j + 1;
		} else if (exp[j] == '.') {
			right.push(exp.substr(i, j - i));
			i = j + 1;
		} else if (exp[j] == '@') {
			break;
		}
	}
	while (!right.empty()) {
		string elem = right.front();
		if (elem == "+") {
			int a = left.top();
			left.pop();
			int b = left.top();
			left.pop();
			left.push(b + a);
		} else if (elem == "-") {
			int a = left.top();
			left.pop();
			int b =  left.top();
			left.pop();
			left.push(b - a);
		} else if (elem == "*") {
			int a = left.top();
			left.pop();
			int b = left.top();
			left.pop();
			left.push(b * a);
		} else if (elem == "/") {
			int a = left.top();
			left.pop();
			int b = left.top();
			left.pop();
			left.push(b / a);
		} else {
			left.push(str2num(elem));
		}
		right.pop();
	}
	cout << left.top() << endl;
    return 0;
}

