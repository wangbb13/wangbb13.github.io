#include <iostream>
using namespace std;

int bag[10002] = {0};

int main() {
    int n, m, price;
	cin >> n >> m;
	bag[0] = 1;
	for (int i = 0; i < n; ++i) {
		cin >> price;
		for (int j = m; j >= price; --j) {
			if (bag[j - price] > 0) {
				bag[j] += bag[j - price];
			}
		}
	}
	cout << bag[m] << endl;
    return 0;
}

