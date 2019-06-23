/**
 * Description: out of a circle 
 * Input : n m 
 * Output: a sequence of numbers 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
	cin >> n >> m;
	vector<bool> nums(n);
	for (int i = 0; i < n; ++i) 
		nums[i] = true;
	int p = n - 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			p = ((p + 1)  % n);
			while (!nums[p]) p = ((p + 1)  % n);
		}
		nums[p] = false;
		cout << p + 1 << " ";
	}
    return 0;
}

