/**
 * Description: Energy Necklace 
 * Input : N, \n, energy list 
 * Output: maximum total energy 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> neck(N);
	for (int i = 0; i < N; ++i) 
		cin >> neck[i];
	vector< vector<int> > dp(N, vector<int>(N, 0));	// i: start index, [0, N-1]; l: length, [1, N-2]
	for (int l = 1; l < N - 1; ++l) {
		for (int i = 0; i < N; ++i) {
			int val = 0;
			int li = (i - 1 + N) % N;
			int ri = (i + l) % N;
			int last = neck[li] * neck[ri];
			for (int j = i; j != ri; j = (j + 1) % N) {
				int len1 = j - i;
				if (len1 < 0) 
					len1 = N + len1;
				int len2 = l - 1 - len1;
				int si2 = (j + 1) % N;
				val = max(val, last * neck[j] + dp[i][len1] + dp[si2][len2]);
			}
			dp[i][l] = val;
			// cout << "[" << i << ", " << l << "] = " << dp[i][l] << endl;
		}
	}
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			int extra = neck[i] * neck[j];
			if (neck[i] > neck[j]) 
				extra *= neck[i];
			else
				extra *= neck[j];
			int len1 = j - i - 1;
			int len2 = N - 2 - len1;
			int si1 = (i + 1) % N;
			int si2 = (j + 1) % N;
			extra += dp[si1][len1] + dp[si2][len2];
			ans = max(extra, ans);
		}
	}
	cout << ans << endl;
    return 0;
}

