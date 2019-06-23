/**
 * Description: maximum sum of a sub-array
 * Input : N \n N numbers
 * Output: maximum value
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
using namespace std;

#define max(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int n, ans, num, p;
	cin >> n >> ans;
	p = max(ans, 0);
	for (int i = 0; i < n - 1; ++i) {
		cin >> num;
		p += num;
		ans = max(ans, p);
		p = max(p, 0);
	}
	cout << ans << endl;
    return 0;
}

