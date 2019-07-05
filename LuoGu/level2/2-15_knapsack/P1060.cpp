#include <iostream>
#include <algorithm>
using namespace std;

int v[30];
int w[30];
int bag[30003];

void init(int n) {
	for (int i = 0; i < n; ++i) {
		bag[i] = 0;
	}
}

int main() {
    int N, m, a, b, ans;
	cin >> N >> m;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		v[i] = a;
		w[i] = a * b;
	}
	init(N + 1);
	for (int i = 0; i < m; ++i) { 
		for (int j = N; j >= v[i]; --j) {
			bag[j] = max(bag[j], bag[j - v[i]] + w[i]);
		}
	}
	ans = -1;
	for (int i = 0; i <= N; ++i) { 
		ans = max(ans, bag[i]);
	}
	cout << ans << endl;
    return 0;
}

