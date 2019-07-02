/**
 * Description: split a number sequence
 * Input : M N \n M numbers 
 * Output: split to n slices, s.t., minimum( maximum(sum of a slice) )
 *         the minimum sum
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
using namespace std;

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int N = 100001;
int nums[N];
int n;

// sln1
int func(int si, int m, vector< vector<int> >& mat) {
	if (mat[si][m] != -1) 
		return mat[si][m];
	if (m == 1) {
		mat[si][m] = nums[n] - nums[si];
		return mat[si][m];
	}
	int ans = nums[n];
	for (int i = si + 1; i <= n - m + 1; ++i) {
		ans = min(ans, max(nums[i] - nums[si], func(i, m - 1, mat)));
	}
	mat[si][m] = ans;
	return ans;
}

bool check(int step, int m) {
	int cnt = 0, val = 0;
	for (int i = 1; i <= n;) {
		if (nums[i] > step) return false;
		while ((i <= n) && (val + nums[i] <= step)) {
			val += nums[i];
			i++;
		}
		val = 0;
		cnt++;
		if (cnt > m) return false;
	}
	return true;
}

int main() {
    int m, l = 0, r = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> nums[i];
		r += nums[i];
	}
	// for (int i = 1; i <= n; ++i) 
	// 	nums[i] += nums[i - 1];
	
	// sln1
	// vector< vector<int> > mat(n + 1, vector<int>(m + 1, -1));
	// cout << func(0, m, mat) << endl;
	
	// sln 2
	// vector< vector<int> > mat(n + 1, vector<int>(m + 1, nums[n]));
	// for (int j = 1; j <= n; ++j) 
	// 	mat[j][1] = nums[j];
	// for (int i = 2; i <= m; ++i) {
	// 	for (int j = i; j <= n; ++j) {	// dp[j][i]
	// 		for (int k = i - 1; k < j; ++k) {
	// 			mat[j][i] = min(mat[j][i], max(nums[j] -nums[k], mat[k][i - 1]));
	// 		}
	// 	}
	// }
	// cout << mat[n][m] << endl;

	// sln3
	// binary search
	while (l < r) {
		int mid = (l + r) / 2;
		if (check(mid, m)) 
			r = mid;
		else
			l = mid + 1;
	}
	cout << r << endl;
    return 0;
}

