#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	char ch[103] = {0};
	int stat[26] = {0};
	for (int i = 0; i < 4; ++i) {
		cin.getline(ch, 102);
		for (int j = 0; j < 103 && ch[j] != 0; ++j) {
			stat[(int)(ch[j] - 'A')]++;
		}
		std::fill(ch, ch + 103, 0);
	}
	int mxv = 0;
	for (int i = 0; i < 26; ++i) {
		mxv = std::max(mxv, stat[i]);
	}
	for (int i = mxv; i > 0; --i) {
		for (int j = 0; j < 26; ++j) {
			if (stat[j] >= i) {
				cout << '*';
			} else {
				cout << ' ';
			}
			if (j < 25) cout << ' ';
		}
		cout << endl;
	}
	cout << "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z" << endl;
	return 0;
}
