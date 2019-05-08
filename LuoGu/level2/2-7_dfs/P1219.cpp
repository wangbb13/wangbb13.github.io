#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int ans = 0;
int show = 0;
vector<int> nums(14);
vector<bool> flag(30);

// improve solution
vector<int> row(30);
// vector<bool> column(30);
// vector<bool> pos(30);
// vector<bool> neg(30);

bool column[30] = {false};
bool pos[30] = {false};
bool neg[30] = {false};

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

void sln_2(int s) {
	if (s > N) {
		if (ans < 3) {
			for (int i = 1; i <= N; ++i) {
				cout << row[i] << " ";
			}
			cout << endl;
		}
		ans++;
		return;
	}
	for (int i = 1; i <= N; ++i) {
		if (!column[i] && !pos[i + s] && !neg[i - s + N]) {
			column[i] = true;
			pos[i + s] = true;
			neg[i - s + N] = true;
			row[s] = i;
			sln_2(s + 1);
			column[i] = false;
			pos[i + s] = false;
			neg[i - s + N] = false;
		}
	}
}

int main() {
	cin >> N;
	// std::fill(column.begin(), column.end(), false);
	// std::fill(pos.begin(), pos.end(), false);
	// std::fill(neg.begin(), neg.end(), false);
	sln_2(1);
	cout << ans << endl;
    return 0;
}

