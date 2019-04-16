#include <iostream>
#include <vector>
using namespace std;

static const auto io_sync_off = []() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	return nullptr;
}();

int main() {
    vector<bool> map(1001, false);
	int n, k, m = 0;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> k;
		if (!map[k]) {
			map[k] = true;
			m++;
		}
	}
	cout << m << endl;
	// bool first = true;
	for (int i = 0; i < 1001; ++i) {
		if (map[i]) {
			cout << i << " ";
		}
	}
	cout << endl;
    return 0;
}

