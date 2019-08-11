/*
ID: wangbb21
LANG: C++
TASK: job
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 0x1fffffff;

int naive(vector<int>& nums, vector<int>& jobs, int n) {
	int min_x, min_i, ans = 0;
	size_t len = nums.size();
	vector<int> copy(nums.begin(), nums.end());
	for (int i = 0; i < n; ++i) {
		min_x = copy[0];
		min_i = 0;
		for (size_t j = 1; j < len; ++j) {
			if (min_x > copy[j]) {
				min_x = copy[j];
				min_i = j;
			}
		}
		jobs[i] = min_x;
		ans = max(ans, min_x);
		copy[min_i] += nums[min_i];
	}
	return ans;
}

int main() {
    ofstream fout("job.out");
    ifstream fin("job.in");
    int n, m1, m2;
	fin >> n >> m1 >> m2;
	vector<int> type_a(m1);
	vector<int> type_b(m2);
	for (int i = 0; i < m1; ++i) fin >> type_a[i];
	for (int i = 0; i < m2; ++i) fin >> type_b[i];
	vector<int> joba(n);
	int a_ans = naive(type_a, joba, n);	// A job done. 
	// B machine 
	vector<int> jobb(n);
	naive(type_b, jobb, n);	// B job done
	int l = 0, r = n - 1, b_ans = 0;
	while (l < n) {
		b_ans = max(joba[l] + jobb[r], b_ans);
		l++;
		r--;
	}
	fout << a_ans << " " << b_ans << endl;
    fin.close();
    fout.close();
    return 0;
}

