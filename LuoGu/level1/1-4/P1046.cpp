#include <iostream>
using namespace std;

int main() {
	int list[10];
	int height;
	int ans = 0;
	for (int i = 0; i < 10; ++i)
		cin >> list[i];
	cin >> height;
	height += 30;
	for (int i = 0; i < 10; ++i) {
		if (height >= list[i]) {
			ans += 1;
		}
	}
	cout << ans << endl;
	return 0;
}
