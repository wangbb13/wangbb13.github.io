#include <iostream>
#include <algorithm>
using namespace std;

int T[100002] = {0};

int main() {
    int t, m, time, val, ans = -1;
	cin >> t >> m;
	for (int i = 0; i < m; ++i) {
		cin >> time >> val;
		for (int j = time; j <= t; ++j) {
			T[j] = max(T[j], T[j - time] + val);
		}
	}
	for (int i = 0; i <= t; ++i) {
		ans = max(ans, T[i]);
	}
	cout << ans << endl;
    return 0;
}

