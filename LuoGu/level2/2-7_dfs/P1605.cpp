/**
 * Description: maze 
 * Input : M N T (the number of obstacles) sx, sy fx, fy x, y (T)
 * Output: the number of ways starting from (sx, sy) to (fx, fy)
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
using namespace std;

typedef vector< vector< bool > > Mat2b;

int N, M;
const int dir[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

bool legal(int x, int y) {
	return ((x >= 0 && x < N) && (y >= 0 && y < M));
}

void ways(int cx, int cy, int fx, int fy, 
		  Mat2b& maze, Mat2b& visit, 
		  int& ans) {
	if (cx == fx && cy == fy) {
		ans++;
		return;
	}
	for (int i = 0; i < 4; ++i) {
		int nx = cx + dir[i][0];
		int ny = cy + dir[i][1];
		if (legal(nx, ny) && maze[nx][ny] && visit[nx][ny]) { 
			visit[nx][ny] = false;
			ways(nx, ny, fx, fy, maze, visit, ans);
			visit[nx][ny] = true;
		}
	}
}

int main() {
	int T, x, y;
	int sx, sy, fx, fy;
	cin >> N >> M >> T;
	Mat2b maze(N, vector<bool>(M, true));
	Mat2b visit(N, vector<bool>(M, true));
	cin >> sx >> sy >> fx >> fy;
	sx--; sy--; fx--; fy--;
	for (int i = 0; i < T; ++i) {
		cin >> x >> y;
		x--; y--;
		maze[x][y] = false;
		visit[x][y] = false;
	}
	if (!maze[fx][fy]) {
		cout << 0 << endl;
		return 0;
	}
	int ans = 0;
	visit[sx][sy] = false;
	ways(sx, sy, fx, fy, maze, visit, ans);
	cout << ans << endl;
    return 0;
}

