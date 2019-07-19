/*
ID: wangbb21
LANG: C++
TASK: camelot
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int row, col;
const int Rw = 31;
const int Cl = 27;
const int Mxs = Rw * Cl;
int kingb[Rw][Cl];
int board[Rw][Cl];

int king_jump[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
int knight_jump[8][2] = { {-2, 1}, {2, 1}, {1, -2}, {1, 2}, {-2, -1}, {2, -1}, {-1, -2}, {-1, 2} };

struct _opt {
	vector<int> min_step;
} opt[Rw][Cl];

typedef struct _pos {
	int r, c;
} pos;

typedef struct _posplus {
	int r, c, k;
} posplus;

void clear_board() {
	for (int i = 0; i < row; ++i) 
		for (int j = 0; j < col; ++j) 
			board[i][j] = Mxs;
}

void init_opt(int n) {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			opt[i][j].min_step.resize(n);
			std::fill(opt[i][j].min_step.begin(), opt[i][j].min_step.end(), Mxs);
		}
	}
}

bool legal_pos(int ri, int cj) {
	return ((ri >= 0 && ri < row) && (cj >= 0 && cj < col));
}

void move(int kki, pos ips) {
	if (kki == 0) {
		for (int i = 0; i < row; ++i) 
			for (int j = 0; j < col; ++j) 
				kingb[i][j] = Mxs;
		queue<pos> m_q;
		m_q.push(ips);
		int rx, cy, nx, ny;
		kingb[ips.r][ips.c] = 0;
		opt[ips.r][ips.c].min_step[0] = 0;
		while (!m_q.empty()) {
			rx = m_q.front().r;
			cy = m_q.front().c;
			m_q.pop();
			for (int i = 0; i < 8; ++i) {
				nx = rx + king_jump[i][0];
				ny = cy + king_jump[i][1];
				if (legal_pos(nx, ny) && kingb[rx][cy] + 1 < kingb[nx][ny]) {
					kingb[nx][ny] = kingb[nx][ny];
					opt[nx][ny].min_step[0] = kingb[nx][ny];
					pos ops = { nx, ny };
					m_q.push(ops);
				}
			}
		}
	} else {
		clear_board();
		queue<posplus> m_q;
		posplus pp = { ips.r, ips.c, opt[ips.r][ips.c].min_step[0] };
		// posplus pp = { ips.r, ips.c, kingb[ips.r][ips.c] };
		m_q.push(pp);
		int rx, cy, nx, ny, miks;
		board[ips.r][ips.c] = 0;
		opt[ips.r][ips.c].min_step[kki] = 0;
		while (!m_q.empty()) {
			rx = m_q.front().r;
			cy = m_q.front().c;
			miks = m_q.front().k;
			m_q.pop();
			for (int i = 0; i < 8; ++i) {
				nx = rx + knight_jump[i][0];
				ny = cy + knight_jump[i][1];
				// if (legal_pos(nx, ny) && board[rx][cy] + 1 < board[nx][ny]) {
				// 	int nxt_miks = min(miks, opt[nx][ny].min_step[0]);
				// 	int nxt_miks = min(miks, kingb[nx][ny]);
				// 	board[nx][ny] = board[rx][cy] + 1;
				// 	opt[nx][ny].min_step[kki] = board[nx][ny];
				// 	opt[nx][ny].min_step[0] = nxt_miks;
				// 	posplus ops = { nx, ny, nxt_miks };
				// 	m_q.push(ops);
				// }

				if (legal_pos(nx, ny)) {
					int nxt_miks = min(miks, opt[nx][ny].min_step[0]);
					// int nxt_miks = min(miks, kingb[nx][ny]);
					if (nxt_miks == Mxs && board[rx][cy] + 1 < board[nx][ny]) {
						board[nx][ny] = board[rx][cy] + 1;
						opt[nx][ny].min_step[kki] = board[nx][ny];
						posplus ops = { nx, ny, nxt_miks };
						m_q.push(ops);
					}
					if (nxt_miks < Mxs && 
						nxt_miks + board[rx][cy] + 1 < opt[nx][ny].min_step[0] + opt[nx][ny].min_step[kki]) {
						board[nx][ny] = board[rx][cy] + 1;
						opt[nx][ny].min_step[kki] = board[nx][ny];
						opt[nx][ny].min_step[0] = nxt_miks;
						posplus ops = { nx, ny, nxt_miks };
						m_q.push(ops);
					}
				}
			}
		}
	}
}

int main() {
    ofstream fout("camelot.out");
    ifstream fin("camelot.in");
    fin >> row >> col;
	vector<pos> vpos;
	char lt; 
	int dgt, r, c, kks = 0;
	while (fin >> lt >> dgt) {
		c = (int)(lt - 'A');
		r = dgt - 1;
		pos p = { r, c };
		vpos.push_back(p);
		kks++;
	}
	init_opt(kks);
	for (int i = 0; i < kks; ++i) 
		move(i, vpos[i]);
	// find optimal sln
	int ans = kks * row * col;
	bool flag;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			int one = 0;
			flag = false;
			for (int k = 0; k < kks; ++k) {
				if (opt[i][j].min_step[k] == Mxs) {
					flag = true;
					break;
				}
				one += opt[i][j].min_step[k];
			}
			if (flag) continue;
			ans = min(ans, one);
			// if (ans > one) {
			// 	ans = one;
			// 	cout << i << " " << j << endl;
			// }
		}
	}
	for (int i = 0; i < kks; ++i) 
		cout << opt[3][1].min_step[i] << " ";
	cout << endl;
	fout << ans << endl;
    fin.close();
    fout.close();
    return 0;
}

