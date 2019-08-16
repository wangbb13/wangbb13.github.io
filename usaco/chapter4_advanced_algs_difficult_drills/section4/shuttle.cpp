/*
ID: wangbb21
LANG: C++11
TASK: shuttle
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef struct __stat {
	int marble;
	int pos;
	__stat(int n) {	// W: 0, B: 1
		marble = (1 << n) - 1;
		pos = n;
	}
} m_stat;

bool gb_find = false;

void show(m_stat& st, int n) {
	int ptr = 1 << (2 * n + 1), i = 2 * n;
	for (; i >= 0; --i) {
		ptr >>= 1;
		if (i == st.pos) { cout << " "; continue; }
		if (ptr & st.marble) cout << 'B';
		else cout << 'W';
	}
	cout << endl;
}

inline bool stop(m_stat& st, int n) {
	return ((st.pos == n) && (st.marble == (((1 << n) - 1) << (n + 1))));
}

inline void set_w(int& num, int pos) {	// zero 
	if (num & (1 << pos)) {
		num -= (1 << pos);
	}
}

inline void set_b(int& num, int pos) {	// one 
	num |= (1 << pos);
}

inline bool is_w(int& num, int pos) {	// zero
	return !(num & (1 << pos));
}

inline bool is_b(int& num, int pos)	{	// one
	return (num & (1 << pos));
}

void recur(m_stat& st, int n, vector<int>& nums) {
	if (stop(st, n)) {
		gb_find = true;
		return;
	}
	if (gb_find) return;
	int __l = 2 * n, __r = 0;
	int ptr = 1 << (__l + 1), i = __l;
	for (; i >= 0; --i) {
		ptr >>= 1;
		if (i == st.pos) continue;
		if (!(st.marble & ptr)) {	// 'w'
			if (i == __r) continue; 
			if (i == st.pos + 1) {	// 'w '
				set_w(st.marble, st.pos);
				st.pos++;
				nums.push_back(__l - i + 1);
				recur(st, n, nums);
	if (gb_find) return;
				nums.pop_back();
				set_w(st.marble, st.pos);
				st.pos--;
			}
			if (i >= 2 && i == st.pos + 2 && is_b(st.marble, i - 1)) {	// 'wb '
				set_w(st.marble, st.pos);
				st.pos += 2;
				nums.push_back(__l - i + 1);
				recur(st, n, nums);
	if (gb_find) return;
				nums.pop_back();
				set_w(st.marble, st.pos);
				st.pos -= 2;
			}
		} else {	// 'b'
			if (i == __l) continue;
			if (i + 1 == st.pos) {	// ' b'
				set_b(st.marble, st.pos);
				st.pos--;
				nums.push_back(__l - i + 1);
				recur(st, n, nums);
	if (gb_find) return;
				nums.pop_back();
				set_b(st.marble, st.pos);
				st.pos++;
			}
			if (i + 2 == st.pos) {	// ' wb'
				set_b(st.marble, st.pos);
				st.pos -= 2;
				nums.push_back(__l - i + 1);
				recur(st, n, nums);
	if (gb_find) return;
				nums.pop_back();
				set_b(st.marble, st.pos);
				st.pos += 2;
			}
		}
	}
}

int main() {
    ofstream fout("shuttle.out");
    ifstream fin("shuttle.in");
    int N; fin >> N;
	m_stat st(N);
	// show(st, N);
	vector<int> ans;
	recur(st, N, ans);
	int per = 0;
	for (size_t i = 0; i < ans.size(); ++i) {
		fout << ans[i];
		per++;
		if (per == 20) {
			per = 0;
			if (i != ans.size() - 1)
				fout << endl;
		} else if (i != ans.size() - 1) {
			fout << ' ';
		}
	}
	if (per != 20)
		fout << endl;
    fin.close();
    fout.close();
    return 0;
}

