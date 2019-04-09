#include <iostream>
#include <vector>
using namespace std;

int main() {
	int L, M, a, b, ans;
	cin >> L >> M;
	ans = L + 1;
	vector<bool> flag(L + 1, true);
	for (int i = 0; i < M; ++i) {
		cin >> a >> b;
		for (int j = a; j <= b; ++j) {
			if (flag[j]) {
				ans--;
				flag[j] = false;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
