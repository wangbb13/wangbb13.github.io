/**
 * Description: fill colors
 * Input : n \n a n x n square (0, 1)
 * Output: fill the circle constructed by 1
 * Attention!!: avoid repeated computation when BFS
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

inline bool legal(int x, int y, int n) {
	return (x >= 0 && x < n && y >= 0 && y < n);
}

int main() {
    int n, x = -1, y = -1, l, r;
	cin >> n;
	vector< vector<int> > squa(n, vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> squa[i][j];
		}
	}
	for (int i = 0; i < n; ++i) {
		int j = 0;
		bool flag = false;
		while (j < n && squa[i][j] == 0) j++;
		if (j == n) continue;
		while (j < n && squa[i][j] == 1) j++;
		if (j == n) continue;
		l = j;
		j = n - 1;
		while (j >= 0 && squa[i][j] == 0) j--;
		if (j < 0) continue;
		while (j >= 0 && squa[i][j] == 1) j--;
		if (j < 0) continue;
		r = j;
		for (j = l; j <= r; ++j) {
			if (squa[i][j] == 0) {
				x = i;
				while (x >= 0 && squa[x][j] == 0) x--;
				if (x < 0) continue;
				x = i;
				while (x < n && squa[x][j] == 0) x++;
				if (x == n) continue;
				x = i; y = j;
				flag = true;
				break;
			}
		}
		if (flag) break;
	}
	queue< pair<int, int> > myQ;
	if (legal(x, y, n))
		myQ.push(std::make_pair(x, y));
	int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	while (!myQ.empty()) {
		int x = myQ.front().first;
		int y = myQ.front().second;
		myQ.pop();
		if (squa[x][y] == 2) continue;	// BE CAREFULL !!!!!!!
		squa[x][y] = 2;
		for (int i = 0; i < 4; ++i) {
			int nx = x + dir[i][0];
			int ny = y + dir[i][1];
			if (legal(nx, ny, n) && squa[nx][ny] == 0)
				myQ.push(std::make_pair(nx, ny));
		}
	}
	for (int i = 0; i < n; ++i) {
		cout << squa[i][0];
		for (int j = 1; j < n; ++j) {
			cout << " " << squa[i][j];
		}
		cout << endl;
	}
    return 0;
}

