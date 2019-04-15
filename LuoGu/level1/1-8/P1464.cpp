#include <iostream>
using namespace std;

typedef long long int lli;

int map[21][21][21];
void init() {
	for (int i = 0; i < 21; ++i) {
		for (int j = 0; j < 21; ++j) {
			for (int k = 0; k < 21; ++k) {
				if (i == 0 || j == 0 || k == 0) {
					map[i][j][k] = 1;
				} else if (i < j && j < k) {
					map[i][j][k] = map[i][j][k - 1] + map[i][j - 1][k - 1] - map[i][j - 1][k];
				} else {
					map[i][j][k] = map[i - 1][j][k] + map[i - 1][j - 1][k] + map[i - 1][j][k - 1] - map[i - 1][j - 1][k - 1];
				}
			}
		}
	}
}

int func(lli a, lli b, lli c) {
	if (a <= 0 || b <= 0 || c <= 0) {
		return 1;
	} else if (a > 20 || b > 20 || c > 20) {
		return map[20][20][20];
	} else {
		return map[a][b][c];
	}
}

int main() {
	init();
	lli a, b, c;
	while (true) {
		cin >> a >> b >> c;
		if (a == -1 && b == -1 && c == -1) break;
		cout << "w(" << a << ", " << b << ", " << c << ") = " << func(a, b, c) << endl;
	}
	return 0;
}
