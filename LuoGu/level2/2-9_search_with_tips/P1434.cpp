/**
 * Description: SHOI 2002 skiing 
 * Input : r c \n matrix of height
 * Output: the maximum skiing length
 * Time/Space Limit: 1s/128MB
 * PS: Understand what is memorization. !!!
 */
#include <iostream>
#include <vector>
using namespace std;

#define max(a, b) (a) > (b) ? (a) : (b)
const int N = 101;

// typedef vector< vector<int> > mat2i; 
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int ski[N][N], len[N][N];
int R, C;

inline bool legal(int x, int y) {
	return (x >= 0 && x < R && y >= 0 && y < C);
}

void init() {
	// ski.resize(R);
	// len.resize(R);
	for (int i = 0; i < R; ++i) {
		// ski[i].resize(C);
		// len[i].resize(C);
		for (int j = 0; j < C; ++j) {
			ski[i][j] = 0;
			len[i][j] = 1;
		}
	}
}

int dfs(int x, int y) {
	if (len[x][y] > 1) return len[x][y];
	int& val = len[x][y];
	for (int i = 0; i < 4; ++i) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if (legal(nx, ny) && 
			(ski[nx][ny] > ski[x][y])) {
			val = max(val, dfs(nx, ny) + 1);
		}
	}
	return val;
}

int main() {
	cin >> R >> C;
	init();
	for (int i = 0; i < R; ++i) 
		for (int j = 0; j < C; ++j) 
			cin >> ski[i][j];
	int ans = 1;
	for (int i = 0; i < R; ++i) 
		for (int j = 0; j < C; ++j) 
			ans = max(ans, dfs(i, j));
	cout << ans << endl;
    return 0;
}

