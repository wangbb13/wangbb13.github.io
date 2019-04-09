#include <iostream>
using namespace std;

int main() {
	char word[13] = {0};
	char ch;
	int i = 0, length = 0, first = -1, count = 0, j;
	bool flag = false;
	while ((ch = cin.get()) && (ch != '\n')) {
		word[i++] = ch;
	}
	length = i;
	i = j = 0;
	while ((ch = cin.get())) {
		j++;
		if (ch == ' ' || ch == '\n') {
			if ((i == length) && !flag) {
				if (first == -1) {
					first = j - length - 1;
				}
				count++;
			}
			i = 0;
			flag = false;
			if (ch == '\n') break;
		} else if (flag) {
			continue;
		} else {
			flag = ((ch | 0x20) ^ (word[i] | 0x20));
			if (!flag) i++;
		}
	}
	if (first == -1) cout << -1 << endl;
	else cout << count << " " << first << endl;
	return 0;
}
