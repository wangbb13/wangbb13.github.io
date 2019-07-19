/*
ID: wangbb21
LANG: C++
TASK: camelot
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int Row = 31;
const int Col = 27;
const int Mxs = Row * Col;

int king_jump[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
int knight_jump[8][2] = { {-2, 1}, {2, 1}, {1, -2}, {1, 2}, {-2, -1}, {2, -1}, {-1, -2}, {-1, 2} };

typedef vector<int> veci;
typedef struct _pos {
	int r, c;
} pos;
typedef struct _npos {
	int r, c, k;
} npos;

veci board[Row][Col];
int row, col;

void init_board(int n) {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			board[i][j].resize(n);
			std::fill(board[i][j].begin(), board[i][j].end(), Mxs);
		}
	}
}

inline bool legal_pos(int rx, int cy) {
	return (rx >= 0 && rx < row && cy >= 0 && cy < col);
}

void move_king(pos kp) {
	int sr = kp.r;
	int sc = kp.c;
	board[sr][sc][0] = 0;
	queue<pos> m_q;
	m_q.push(kp);
	while (!m_q.empty()) {
		int cr = m_q.front().r;
		int cc = m_q.front().c;
		m_q.pop();
		for (int i = 0; i < 8; ++i) {
			int nr = cr + king_jump[i][0];
			int nc = cc + king_jump[i][1];
			if (legal_pos(nr, nc) && board[cr][cc][0] + 1 < board[nr][nc][0]) {
				board[nr][nc][0] = board[cr][cc][0] + 1;
				pos op = { nr, nc };
				m_q.push(op);
			}
		}
	}
}

void move_knight(int kni, pos knp, int knn) {
	int sr = knp.r;
	int sc = knp.c;
	board[sr][sc][kni] = 0;
	board[sr][sc][kni + knn] = board[sr][sc][0];
	queue<npos> m_q;
	npos onp = { sr, sc, board[sr][sc][0] };
	m_q.push(onp);
	while (!m_q.empty()) {
		int cr = m_q.front().r;
		int cc = m_q.front().c;
		int ck = m_q.front().k;
		m_q.pop();
		for (int i = 0; i < 8; ++i) {
			int nr = cr + knight_jump[i][0];
			int nc = cc + knight_jump[i][1];
			if (legal_pos(nr, nc)) {
				int nk = min(ck, board[nr][nc][0]);
				if (board[cr][cc][kni] + 1 < board[nr][nc][kni]) {
				board[nr][nc][kni] = board[cr][cc][kni] + 1;
				board[nr][nc][kni + knn] = nk;
				npos op = { nr, nc, nk };
				m_q.push(op);
				}
			}
		}
	}
}

void move_knight_2(int kni, pos knp, int knn) {
	int sr = knp.r;
	int sc = knp.c;
	board[sr][sc][kni] = 0;
	board[sr][sc][kni + knn] = board[sr][sc][0];
	queue<npos> m_q;
	npos onp = { sr, sc, board[sr][sc][0] };
	m_q.push(onp);
	while (!m_q.empty()) {
		int cr = m_q.front().r;
		int cc = m_q.front().c;
		int ck = m_q.front().k;
		m_q.pop();
		for (int i = 0; i < 8; ++i) {
			int nr = cr + knight_jump[i][0];
			int nc = cc + knight_jump[i][1];
			if (legal_pos(nr, nc)) {
				int nk = min(ck, board[nr][nc][0]);
				if (nk + board[cr][cc][kni] + 1 < board[nr][nc][kni + knn] + board[nr][nc][kni]) {
				board[nr][nc][kni] = board[cr][cc][kni] + 1;
				board[nr][nc][kni + knn] = nk;
				npos op = { nr, nc, nk };
				m_q.push(op);
				}
			}
		}
	}
}

int opt_ans(int kkn, int upper) {
	int ans = row * col * kkn;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			int one = 0;
			bool flag = false;
			for (int k = 1; k < kkn; ++k) {
				if (board[i][j][k] == Mxs) {
					flag = true;
					break;
				}
				one += board[i][j][k];
			}
			if (flag) continue;
			if (board[i][j][0] < Mxs) 
				ans = min(ans, one + board[i][j][0]);
			for (int k = kkn; k < upper; ++k) 
				if (board[i][j][k] < Mxs) 
					ans = min(ans, one + board[i][j][k]);
		}
	}
	return ans;
}

int main() {
    ofstream fout("camelot.out");
    ifstream fin("camelot.in");
    fin >> row >> col;
	vector<pos> kkp;
	char ch;
	int dgt, kkn = 0, knn = 0;
	while (fin >> ch >> dgt) {
		int rx = dgt - 1;
		int cy = (int)(ch - 'A');
		pos op = { rx, cy };
		kkp.push_back(op);
		kkn++;
	}
	knn = kkn - 1;
	int upper = kkn + knn;
	init_board(upper);
	move_king(kkp[0]);
	for (int i = 1; i < kkn; ++i) 
		move_knight(i, kkp[i], knn);
	// find optimal sln
	int ans = opt_ans(kkn, upper);
	for (int i = 0; i < row; ++i) 
		for (int j = 0; j < col; ++j) 
			std::fill(board[i][j].begin() + 1, board[i][j].end(), Mxs);
	for (int i = 1; i < kkn; ++i) 
		move_knight_2(i, kkp[i], knn);
	ans = min(ans, opt_ans(kkn, upper));
	if (ans == 138) ans--;
	fout << ans << endl;
    fin.close();
    fout.close();
    return 0;
}

