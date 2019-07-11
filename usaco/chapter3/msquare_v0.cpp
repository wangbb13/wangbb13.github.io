/*
ID: wangbb21
LANG: C++
TASK: msquare
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <unordered_set>
using namespace std;

typedef unsigned int uint;

uint Bits[8][2];

void show(uint n) {
	for (int i = 31; i >= 0; --i) {
		if (n & (1 << i)) cout << 1;
		else cout << 0;
	}
	cout << endl;
}

void show4(uint n) {
	uint flag = 15;
	for (int i = 0; i < 8; ++i) 
		cout << ((n & (flag << (i * 4))) >> (i * 4)) << " ";
	cout << endl;
}

void init() {
	uint flag = 15;
	for (int i = 0; i < 8; ++i) {
		Bits[i][0] = flag << (i * 4);
		Bits[i][1] = ~Bits[i][0];
	}
}

void t_swap(uint& num, int i, int j) {	// i < j
	uint ui = num & Bits[i][0];
	uint uj = num & Bits[j][0];
	ui <<= ((j - i) * 4);
	uj >>= ((j - i) * 4);
	num &= Bits[i][1];
	num &= Bits[j][1];
	num |= ui;
	num |= uj;
}

void tA(uint& num) {
	for (int i = 0; i < 4; ++i) 
		t_swap(num, i, 7 - i);
}

void tB(uint& num) {
	for (int i = 2; i >= 0; --i) 
		t_swap(num, i, i + 1);
	for (int i = 4; i < 7; ++i) 
		t_swap(num, i, i + 1);
}

void tC(uint& num) {
	t_swap(num, 1, 2);
	t_swap(num, 1, 6);
	t_swap(num, 5, 6);
}

typedef struct _status {
	uint ui_n;
	string s_t;
} status;

bool check(ofstream& fout, ifstream& fin, uint sp, status& x) {
	if (x.ui_n == sp) {
		size_t len = x.s_t.size();
		fout << len << endl;
		int pos = 0;
		while (pos < len) {
			fout << x.s_t.substr(pos, 60) << endl;
			pos += 60;
		}
		if (len == 0) fout << endl;
		fin.close();
		fout.close();
		return true;
	}
	return false;
}

int main() {
    ofstream fout("msquare.out");
    ifstream fin("msquare.in");
    init();
	uint fn = 0, sp = 0, x;
	for (int i = 1; i <= 8; ++i) {
		fn |= (i << (4 * (i - 1)));
		fin >> x;
		sp |= (x << (4 * (i - 1)));
	}
	queue<status> mq;
	status fs = { fn, "" };
	if (check(fout, fin, sp, fs)) return 0;
	status ans;
	mq.push(fs);
	bool ba, bb, bc;
	unordered_set<uint> found;
	found.insert(fn);
	while (!mq.empty()) {
		status st = mq.front();
		mq.pop();
		size_t s_len = st.s_t.size();
		ba = bb = bc = true;
		if (s_len > 0 && st.s_t[s_len - 1] == 'A') ba = false;
		if (s_len > 2 && st.s_t.substr(s_len - 3) == "BBB") bb = false;
		if (s_len > 2 && st.s_t.substr(s_len - 3) == "CCC") bc = false;
		if (ba) {
			uint x = st.ui_n;
			tA(x);
			status nxA = { x, st.s_t + "A" };
			if (check(fout, fin, sp, nxA)) return 0;
			else if (found.find(x) == found.end()) { 
				mq.push(nxA);
				found.insert(x);
			}
		}
		if (bb) {
			uint x = st.ui_n;
			tB(x);
			status nxB = { x, st.s_t + "B" };
			if (check(fout, fin, sp, nxB)) return 0;
			else if (found.find(x) == found.end()) {
				mq.push(nxB);
				found.insert(x);
			}
		}
		if (bc) {
			uint x = st.ui_n;
			tC(x);
			status nxC = { x, st.s_t + "C" };
			if (check(fout, fin, sp, nxC)) return 0;
			else if (found.find(x) == found.end()) {
				mq.push(nxC);
				found.insert(x);
			}
		}
	}
    fin.close();
    fout.close();
    return 0;
}

