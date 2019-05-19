/**
 * Description: the sum of continuous number
 * Input : M
 * Output: several intervals of which the sum is equal to M
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
using namespace std;

int main() {
    int M;
	cin >> M;
	for (int i = M / 2; i > 1; --i) {
		int iQuo = M / i;
		if (i % 2 == 1) {
			if (M % i == 0) {
				if (iQuo - (i / 2) > 0)
					cout << iQuo - (i / 2) << " " << iQuo + (i / 2) << endl;
			}
		} else {
			if (M % i == (i / 2)) {
				if (iQuo - (i / 2) + 1 > 0)
					cout << iQuo - (i / 2) + 1 << " " << iQuo + (i / 2) << endl;
			}
		}
	}
    return 0;
}

