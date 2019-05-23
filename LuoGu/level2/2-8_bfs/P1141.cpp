/**
 * Description: move in a square (01 square)
 * Input : n (square), m (# queries) \n ...
 * Output: the number of grids to which we can move from a specified point
 * Time/Space Limit: 1s/128MB
 * Attention: AVOID REPEATED COMPUTATION ADN STORAGE !!!!!!!!!!
 */
#include <iostream>
#include <vector>
#include <utility>	// make_pair, pair
#include <queue>
using namespace std;

typedef vector< vector<int> > mat2i;
typedef vector< vector<bool> > mat2b;

// mat2b status;
vector<int> mem;

template <typename Mat, typename T>
void init_mat(Mat& mat, int n, int m, T val) {
	if (mat.size() == n && mat.size() > 0 && mat[0].size() == m) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				mat[i][j] = val;
			}
		}
		return;
	}
	mat.resize(n);
	for (int i = 0; i < n; ++i) {
		mat[i].resize(m);
		for (int j = 0; j < m; ++j) {
			mat[i][j] = val;
		}
	}
}

inline bool legal(int x, int y, int n) {
	return (x >= 0 && x < n && y >= 0 && y < n);
}

void tranverse(const mat2i& maze, int x, int y, mat2i& info) {
	int n = maze.size();
	// init_mat<mat2b, bool>(status, n, n, false);
	int nums = 0;
	queue< pair<int, int> > myQ;
	myQ.push(std::make_pair(x, y));
	int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	int mi = 0;
	while (!myQ.empty()) {
		int px = myQ.front().first;
		int py = myQ.front().second;
		myQ.pop();
		// if (status[px][py]) continue;
		// status[px][py] = true;
		if (info[px][py] > 0) continue;
		nums++;
		info[px][py] = nums;
		mem[mi] = px;
		mem[mi + 1] = py;
		mi += 2;
		for (int i = 0; i < 4; ++i) {
			int nx = px + dir[i][0];
			int ny = py + dir[i][1];
			if (legal(nx, ny, n) && maze[px][py] != maze[nx][ny]) {
				myQ.push(std::make_pair(nx, ny));
			}
		}
	}
	for (int i = 0; i < mi; i += 2) {
		info[mem[i]][mem[i + 1]] = nums;
	}
}

int main() {
    int n, m, n_sq;
	cin >> n >> m;
	mat2i maze;
	mat2i info;
	init_mat<mat2i, int>(maze, n, n, 0);
	init_mat<mat2i, int>(info, n, n, 0);
	// init_mat<mat2b, bool>(status, n, n, false);
	n_sq = n * n;
	mem.resize(n_sq * 2);
	char ch;
	int i = 0, j = 0;
	while (n_sq > 0) {
		cin.get(ch);
		if (ch == '0' || ch == '1') {
			maze[i][j] = (ch == '0') ? (0) : (1);
			j++;
			if (j == n) {
				i++;
				j = 0;
			}
			n_sq--;
		}
	}
	// for (i = 0; i < n; ++i) {
	// 	for (j = 0; j < n; ++j) {
	// 		if (info[i][j] > 0) continue;
	// 		tranverse(maze, i, j, info);
	// 	}
	// }
	int x, y;
	for (i = 0; i < m; ++i) {
		cin >> x >> y;
		if (info[x - 1][y - 1] == 0)
			tranverse(maze, x - 1, y - 1, info);
		cout << info[x - 1][y - 1] << endl;
	}
    return 0;
}

