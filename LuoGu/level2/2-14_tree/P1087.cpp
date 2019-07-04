/**
 * Description: FBI tree, all 0: B, all 1: I, [01]+: F
 * Input : N \n 2^N 0|1
 * Output: postorder traversal of FBI tree
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <string>
#include <stack>
using namespace std;

typedef struct _level {
	char ch;
	int lvl;
} level;

int main() {
    int n;
	cin >> n;
	string str;
	cin >> str;
	stack<level> m_stack;
	for (int i = 0; i < str.size(); ++i) {
		char ch = str[i];
		level el;
		el.lvl = 0;
		if (ch == '1') 
			el.ch = 'I';
		else
			el.ch = 'B';
		cout << el.ch;
		if (!(!m_stack.empty() && m_stack.top().lvl == el.lvl)) {
			m_stack.push(el);
			continue;
		}
		while (!m_stack.empty() && m_stack.top().lvl == el.lvl) {
			if (m_stack.top().ch != el.ch) 
				el.ch = 'F';
			el.lvl++;
			m_stack.pop();
			cout << el.ch;
		}
		m_stack.push(el);
	}
	cout << endl;
    return 0;
}

