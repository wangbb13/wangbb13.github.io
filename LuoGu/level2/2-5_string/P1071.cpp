/**
 * Description: password (simple) 
 * Input : ...
 * Output: ...
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<bool> from(26, true);
	vector<int> map(26, -1);
	string entropy, origin, text;
	cin >> origin >> entropy >> text;
	int nums = 0;
	bool flag = false;
	for (size_t i = 0; i < origin.size(); ++i) {
		int x = origin[i] - 'A';
		int y = entropy[i] - 'A';
		if (from[y]) {
			from[y] = false;
			nums++;
		}
		if (map[x] == -1) {
			map[x] = y;
		} else if (map[x] != y) {
			flag = true;
			break;
		}
	}
	if (nums != 26 || flag) {
		cout << "Failed" << endl;
	} else {
		for (size_t i = 0; i < text.size(); ++i) {
			cout << (char)('A' + map[text[i] - 'A']);
		}
		cout << endl;
	}
    return 0;
}

