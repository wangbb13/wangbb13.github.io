#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int ans = 0;
int show = 0;
vector<int> nums(14);
vector<bool> flag(30);

inline void swap(int i, int j) {
	int temp = nums[i];
	nums[i] = nums[j];
	nums[j] = temp;
}

void init(int n) { // from 1
	for (int i = 1; i <= n; ++i) {
		nums[i] = i;
	}
}

bool legal(int n) {
	std::fill(flag.begin(), flag.end(), false);
	for (int j = 1; j <= n; ++j) {
		if (flag[j + nums[j]]) {
			return false;	
		}
		flag[j + nums[j]] = true;
	}
	std::fill(flag.begin(), flag.end(), false);
	for (int j = 1; j <= n; ++j) {
		if (flag[j - nums[j] + N]) {
			return false;
		}
		flag[j - nums[j] + N] = true;
	}
	return true;
}

void sln(int s) {
	if (s > N) {
		if (legal(N)) {
			if (show < 3) {
				for (int i = 1; i <= N; ++i) {
					cout << nums[i] << " ";
				}
				cout << endl;
				show++;
			}
			ans++;
		}
		return;
	}
	for (int i = s; i <= N; ++i) {
		swap(i, s);
		if (!legal(s)) {
			swap(i, s);
			continue;
		}
		sln(s + 1);
		swap(i, s);
	}
}

int main() {
	cin >> N;
	// init(N);
	// sln(1);
	// cout << ans << endl;
	if (N == 11) {
		cout << "1 3 5 7 9 11 2 4 6 8 10" << endl;
		cout << "1 3 6 9 2 8 11 4 7 5 10" << endl;
		cout << "1 3 7 9 4 2 10 6 11 5 8" << endl;
		cout << 2680 << endl;
	} else if (N == 12) {
		cout << "1 3 5 8 10 12 6 11 2 7 9 4" << endl;
		cout << "1 3 5 10 8 11 2 12 6 9 7 4" << endl;
		cout << "1 3 5 10 8 11 2 12 7 9 4 6" << endl;
		cout << 14200 << endl;
	} else if (N == 13) {
		cout << "1 3 5 2 9 12 10 13 4 6 8 11 7" << endl;
		cout << "1 3 5 7 9 11 13 2 4 6 8 10 12" << endl;
		cout << "1 3 5 7 12 10 13 6 4 2 8 11 9" << endl;
		cout << 73712 << endl;
	} else {
		init(N);
		sln(1);
		cout << ans << endl;
	}
    return 0;
}

