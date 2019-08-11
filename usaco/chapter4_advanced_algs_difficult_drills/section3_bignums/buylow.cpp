/*
ID: wangbb21
LANG: C++11
TASK: buylow
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

const int N = 100;

void m_add(vector<int>& a, vector<int>& b) {	// a += b
	int carry = 0;
	for (int i = N - 1; i >= 0; --i) {
		a[i] = a[i] + b[i] + carry;
		carry = a[i] / 10;
		a[i] %= 10;
	}
}

void to_one(vector<int>& num) {
	for (int i = 0; i < N - 1; ++i) 
		num[i] = 0;
	num[N - 1] = 1;
}

void m_assign(vector<int>& a, vector<int>& b) { // a = b
	for (size_t i = 0; i < a.size(); ++i) 
		a[i] = b[i];
}

int main() {
    ofstream fout("buylow.out");
    ifstream fin("buylow.in");
    int n; fin >> n; 
	vector<int> prices(n);
	for (int i = 0; i < n; ++i) fin >> prices[i];
	vector<int> dp(n, 1);
	vector< vector<int> > cnt(n, vector<int>(N, 0));
	for (int i = 0; i < n; ++i) 
		cnt[i][N - 1] = 1;
	int max_val;
	vector<int> max_cnt(N);
	int ans_val = 1;
	vector<int> ans_cnt(N, 0);
	unordered_set<int> cand;
	for (int i = n - 2; i >= 0; --i) {
		max_val = 0; 
		to_one(max_cnt);
		cand.clear();
		for (int j = i + 1; j < n; ++j) {
			if (prices[i] > prices[j]) {
				if (dp[j] > max_val) {
					max_val = dp[j];
					cand.clear();
					cand.insert(prices[j]);
					// max_cnt = cnt[j];
					m_assign(max_cnt, cnt[j]);
				} else if (dp[j] == max_val && cand.find(prices[j]) == cand.end()) {
					cand.insert(prices[j]);
					// max_cnt += cnt[j];
					m_add(max_cnt, cnt[j]);
				}
			}
		}
		dp[i] = max_val + 1;
		// cnt[i] = max_cnt;
		m_assign(cnt[i], max_cnt);
		ans_val = max(ans_val, dp[i]);
	}
	cand.clear();
	for (int i = 0; i < n; ++i) {
		if (dp[i] == ans_val && cand.find(prices[i]) == cand.end()) {
			// ans_cnt += cnt[i];
			m_add(ans_cnt, cnt[i]);
			cand.insert(prices[i]);
		}
	}
	fout << ans_val << " ";
	int i = 0;
	while (i < N && ans_cnt[i] == 0) i++;
	// if (i == N) fout << 0;
	while (i < N) fout << ans_cnt[i++];
	fout << endl;
    fin.close();
    fout.close();
    return 0;
}

