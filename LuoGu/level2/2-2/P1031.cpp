#include <iostream>
using namespace std;

int pile[100] = {0};

int main() {
    int N, avg = 0, ans = 0;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> pile[i];
		avg += pile[i];
	}
	avg /= N;
	int cum = 0;
	for (int i = 0; i < N; ++i) {
		cum += (pile[i] - avg);
		if (cum != 0) 
			ans++;
	}
	cout << ans << endl;
    return 0;
}
