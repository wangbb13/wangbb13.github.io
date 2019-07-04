/**
 * Description: symmetric binary tree 
 * Input : tree 
 * Output: maximum # nodes of a symmetric substree
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
using namespace std;

#define max(a, b) (a) > (b) ? (a) : (b)

const int N = 1000003;
int tree[N][2];
int nums[N];
int vals[N];

void dfs(int ni) {
	int ans = 1;
	if (tree[ni][0] > 0) {
		dfs(tree[ni][0]);
		ans += nums[tree[ni][0]];
	}
	if (tree[ni][1] > 0) {
		dfs(tree[ni][1]);
		ans += nums[tree[ni][1]];
	}
	nums[ni] = ans;
}

bool check(int lhs, int rhs) {
	if (lhs == -1 && rhs == -1) 
		return true;
	if (lhs != -1 && rhs != -1 && vals[lhs] == vals[rhs] && 
		check(tree[lhs][0], tree[rhs][1]) && 
		check(tree[lhs][1], tree[rhs][0]) )
		return true;
	return false;
}

int main() {
    int n, ans;
	cin >> n;
	for (int i = 1; i <= n; ++i) 
		cin >> vals[i];
	for (int i = 1; i <= n; ++i) 
		cin >> tree[i][0] >> tree[i][1];
	dfs(1);
	for (int i = 1; i <= n; ++i) 
		if (check(tree[i][0], tree[i][1])) 
			ans = max(ans, nums[i]);
	cout << ans << endl;
    return 0;
}

