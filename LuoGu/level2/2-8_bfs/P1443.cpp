/**
 * Description: the traverse of horse style move 
 * Input : n m x y 
 * Output: the minimum number of steps to each point from (x, y)
 * Time/Space Limit: 1s/128MB
 * Attention: BE CAREFUL ABOUNT THE REPEATED POINT WHEN CONDUCT BGS !!!!
 */
#include <iostream>
#include <cstdio>
using namespace std;

const int N = 401;

int board[N][N];

void init(int n, int m) {
	for (int i = 0; i < n; ++i) 
		for (int j = 0; j < m; ++j)
			board[i][j] = -1;
}

inline bool is_legal(int x, int y, int n, int m) {
	return (x >= 0 && x < n &&  y >= 0 && y < m);
}

int main() {
    int n, m, x, y, ps;
	cin >> n >> m >> x >> y;
	init(n, m);
	x--; y--;
	int steps = 0;
	ps = n * m * 2;
	int *cur = new int[ps];
	int *nxt = new int[ps];
	int cur_size = 2;
	cur[0] = x; cur[1] = y;
	int dir[8][2] = { {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, 
	                  {1, -2}, {2, -1}, {2, 1}, {1, 2} };
	while (cur_size > 0) {
		int nxt_i = 0;
		for (int i = 0; i < cur_size; i += 2) {
			int px = cur[i];
			int py = cur[i + 1];
			board[px][py] = steps;
			for (int j = 0; j < 8; ++j) {
				int nx = px + dir[j][0];
				int ny = py + dir[j][1];
				if (is_legal(nx, ny, n, m) && board[nx][ny] == -1) {
					nxt[nxt_i] = nx;
					nxt[nxt_i + 1] = ny;
					nxt_i += 2;
					board[nx][ny] = -2;
				}
			}
		}
		cur_size = nxt_i;
		int *temp = cur;
		cur = nxt;
		nxt = temp;
		steps++;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			printf("%-5d", board[i][j]);
		}
		cout << endl;
	}
    return 0;
}

