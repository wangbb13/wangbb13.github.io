/**
 * Description: point binary tree 
 * Input : sequential traversal 
 * Output: maximum point &
 *         its preorder traversal 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
using namespace std;

const int N = 31;
struct __tree {
	uint64_t score;
	int root;
} dp[N][N];

void pre_order(int l, int r) {
	if (l > r) 
		return;
	int root = dp[l][r].root;
	cout << root + 1 << " ";
	pre_order(l, root - 1);
	pre_order(root + 1, r);
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> dp[i][i].score;
		dp[i][i].root = i;
	}
	for (int i = 2; i <= n; ++i) {
		for (int j = 0; (i + j - 1) < n; ++j) {	// dp[j][j + i - 1]
			int max_val = 0, max_rot = 0;
			int c_s, l_s, r_s, __s;
			for (int k = j; k < j + i; ++k) {
				c_s = dp[k][k].score;
				if (k > j) 
					l_s = dp[j][k - 1].score;
				else 
					l_s = 1;
				if (k < j + i - 1) 
					r_s = dp[k + 1][j + i - 1].score;
				else 
					r_s = 1;
				__s = c_s + l_s * r_s;
				if (__s > max_val) {
					max_val = __s;
					max_rot = k;
				}
			}
			dp[j][j + i - 1].score = max_val;
			dp[j][j + i - 1].root = max_rot;
		}
	}
	cout << dp[0][n - 1].score << endl;
	pre_order(0, n - 1);
    return 0;
}

