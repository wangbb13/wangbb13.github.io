/*
ID: wangbb21
LANG: C++11
TASK: frameup
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int WH = 30;
const int LE = 26;

const int SPACE = 27;
const int ERASE = 28;

bool letter[LE];
int _frame[WH][WH];

typedef struct __pos {
	int lux, luy;
	int rbx, rby;
	__pos() {
		lux = luy = WH + 1;
		rbx = rby = 0;
	}
} pos;

pos every_pos[LE];

bool check(int x) {
	for (int i = every_pos[x].lux; i <= every_pos[x].rbx; ++i) {
		if (_frame[i][every_pos[x].luy] != x && _frame[i][every_pos[x].luy] != ERASE) return false;
		if (_frame[i][every_pos[x].rby] != x && _frame[i][every_pos[x].rby] != ERASE) return false;
	}
	for (int i = every_pos[x].luy; i <= every_pos[x].rby; ++i) {
		if (_frame[every_pos[x].lux][i] != x && _frame[every_pos[x].lux][i] != ERASE) return false;
		if (_frame[every_pos[x].rbx][i] != x && _frame[every_pos[x].rbx][i] != ERASE) return false;
	}
	return true;
}

vector<string> ans;
int tot_n = 0, h, w;

void _move(int (&a)[WH][WH], int (&b)[WH][WH]) {	// a = b
	for (int i = 0; i < h; ++i) 
		for (int j = 0; j < w; ++j) 
			a[i][j] = b[i][j];
}

void _f_erase(int x) {
	for (int i = every_pos[x].lux; i <= every_pos[x].rbx; ++i) 
		_frame[i][every_pos[x].luy] = _frame[i][every_pos[x].rby] = ERASE;
	for (int i = every_pos[x].luy; i <= every_pos[x].rby; ++i) 
		_frame[every_pos[x].lux][i] = _frame[every_pos[x].rbx][i] = ERASE;
}

void dfs(string str, int len) {
	if (len == tot_n) {
		std::reverse(str.begin(), str.end());
		ans.push_back(str);
		return;
	}
	for (int i = 0; i < LE; ++i) {
		if (!letter[i]) continue;
		if (!check(i)) continue;
		int temp[WH][WH];
		_move(temp, _frame);
		_f_erase(i);
		letter[i] = false;
		dfs(str + (char)('A' + i), len + 1);
		letter[i] = true;
		_move(_frame, temp);
	}
}

int main() {
	ofstream fout("frameup.out");
	ifstream fin("frameup.in");
	fin >> h >> w;
	char ch;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			fin >> ch;
			if (ch == '.') _frame[i][j] = SPACE;
			else if (ch >= 'A' && ch <= 'Z') {
				int ln = (int)(ch - 'A');
				_frame[i][j] = ln;
				if (!letter[ln]) tot_n++;
				letter[ln] = true;
				every_pos[ln].lux = std::min(every_pos[ln].lux, i);
				every_pos[ln].luy = std::min(every_pos[ln].luy, j);
				every_pos[ln].rbx = std::max(every_pos[ln].rbx, i);
				every_pos[ln].rby = std::max(every_pos[ln].rby, j);
			}
		}
	}
	string str_init = "";
	dfs(str_init, 0);
	std::sort(ans.begin(), ans.end());
	for (auto &elem : ans) 
		fout << elem << endl;
    fin.close();
    fout.close();
    return 0;
}

