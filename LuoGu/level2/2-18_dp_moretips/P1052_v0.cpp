#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int L, S, T, M;

void dfs(vector<int>& steps, vector<int>& stones, int i) {
	if (i >= L) return; 
	for (int j = S; j <= T; ++j) {
		if (i + j >= L) return;
		steps[i + j] = min(steps[i] + stones[i + j], steps[i + j]);
		// cout << "steps[" << i << "] = " << steps[i] << ", stones[" << i + j << "] = " << stones[i + j] << ", steps[" << i + j << "] = " << steps[i + j] << endl;
		dfs(steps, stones, i + j);
	}
}

int main() {
	cin >> L >> S >> T >> M;
	vector<int> stones(L, 0);
	vector<int> steps(L, M + 1);
	int a;
	for (int i = 0; i < M; ++i) {
		cin >> a;
		stones[a] = 1;
	}
	steps[0] = 0;
	dfs(steps, stones, 0);
	int ans = M + 1;
	for (int i = max(0, L - T); i < L; ++i) {
		if (steps[i] < M + 1) {
			ans = min(ans, steps[i]);
		}
	}
	cout << ans << endl;
	return 0;
}
