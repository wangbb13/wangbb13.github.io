#include <iostream>
using namespace std;

int main() {
	int n, temp1, temp2, ans = 1, cont = 1;
	cin >> n;
	cin >> temp1;
	for (int i = 1; i < n; ++i) {
		cin >> temp2;
		if (temp2 > temp1) {
			cont++;
		} else {
			ans = cont > ans ? cont : ans;
			cont = 1;
		}
		temp1 = temp2;
	}
	ans = cont > ans ? cont : ans;
	cout << ans << endl;
	return 0;
}
