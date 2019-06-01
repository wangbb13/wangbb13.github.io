/**
 * Description: Fast mod operation
 * Input : b, p, k
 * Output: b^p % k
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long int ull;

ull fast_mod(ull b, ull p, ull k) {
	if (p == 0) 
		return (ull)(1 % k);
	ull ans = fast_mod(b, p / 2, k);
	ans = (ans * ans) % k;
	if (p % 2 == 1) 
		ans = (ans * b) % k;
	return ans;
	// if (p == 0) 
	// 	return 1 % k;
	// vector<ull> temp(100);
	// vector<ull> flag(100);
	// ull ans = b % k;
	// temp[0] = ans;
	// flag[0] = 1;
	// ull cur = 1, nxt = 2;
	// size_t i = 1;
	// while (nxt <= p) {
	// 	ans = (ans * ans) % k;
	// 	temp[i] = ans;
	// 	flag[i] = nxt;
	// 	cur = nxt;
	// 	nxt *= 2;
	// 	i++;
	// }
	// p -= cur;
	// while (p > 0) {
	// 	for (size_t j = 0; j < i - 1; ++j) {
	// 		if (flag[j] <= p && flag[j + 1] > p) {
	// 			ans = (ans * temp[j]) % k;
	// 			p -= flag[j];
	// 			break;
	// 		}
	// 	}
	// }
	// return ans;
}

int main() {
    ull b, p, k;
	cin >> b >> p >> k;
	cout << b << "^" << p << " mod " << k << "=" << fast_mod(b, p, k) << endl;
    return 0;
}

