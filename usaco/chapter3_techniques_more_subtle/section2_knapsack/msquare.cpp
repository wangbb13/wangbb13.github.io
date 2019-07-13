/*
ID: wangbb21
LANG: C++
TASK: msquare
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
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

typedef struct _node {
	int a, b, c;
} node;

const int n_nodes = 40320;
vector<node> graph(n_nodes);
unordered_map<uint, int> cnid_map;
int gnid = 0;
const int inf = n_nodes + 1;

int compress(vector<int>& nums) {
	int ans = 0;
	for (int i = 0; i < 8; ++i) 
		ans |= (nums[i] << (4 * i));
	return ans;
}

void build_graph(vector<int>& nums, int si) {
	if (si == 8) {
		int c_num = compress(nums);
		cnid_map[c_num] = gnid;
		gnid++;
		return;
	}
	for (int i = si; i < 8; ++i) {
		int temp = nums[si];
		nums[si] = nums[i];
		nums[i] = temp;
		build_graph(nums, si + 1);
		temp = nums[si];
		nums[si] = nums[i];
		nums[i] = temp;
	}
}

int main() {
    ofstream fout("msquare.out");
    ifstream fin("msquare.in");
    init();
	uint fn = 0, sp = 0, x;
	vector<int> nums(8);
	for (int i = 1; i <= 8; ++i) {
		fn |= (i << (4 * (i - 1)));
		fin >> x;
		sp |= (x << (4 * (i - 1)));
		nums[i - 1] = i;
	}
	// special 
	if (fn == sp) {
		fout << 0 << endl << endl;
		fin.close(); fout.close();
		return 0;
	}
	// buld graph 
	build_graph(nums, 0);
	unordered_map<uint, int>::iterator it;
	for (it = cnid_map.begin(); it != cnid_map.end(); ++it) {
		int nid = it->second;
		uint x = it->first;
		tA(x);
		graph[nid].a = cnid_map[x];
		x = it->first;
		tB(x);
		graph[nid].b = cnid_map[x];
		x = it->first;
		tC(x);
		graph[nid].c = cnid_map[x];
	}
	// dijkstra 
	vector<int> parent(n_nodes, -1);
	vector<bool> visit(n_nodes, true);
	vector<int> ssp(n_nodes, inf);
	int snid = cnid_map[fn], tnid = cnid_map[sp];
	visit[snid] = false;
	ssp[snid] = 0;
	vector<int>* cur = new vector<int>(n_nodes);
	vector<int>* nxt = new vector<int>(n_nodes);
	int border_n = 1;
	(*cur)[0] = snid;
	bool flag;
	vector<bool> second(n_nodes);
	while (true) {
		int nxt_border = 0;
		flag = false;
		std::fill(second.begin(), second.end(), true);
		for (int bi = 0; bi < border_n; ++bi) {
			int nid = (*cur)[bi];
			vector<int> nbrs = { graph[nid].a, graph[nid].b, graph[nid].c };
			for (int i = 0; i < 3; ++i) {
				int nbr = nbrs[i];
				if (visit[nbr]) {
					if (nbr == tnid) flag = true;
					if (second[nbr]) {
						(*nxt)[nxt_border++] = nbr;
						second[nbr] = false;
					}
					if (ssp[nid] + 1 < ssp[nbr]) {
						ssp[nbr] = ssp[nid] + 1;
						parent[nbr] = nid;
					}
					// if (ssp[nid] + 1 == ssp[nbr]) {
					// 	int j = 0;
					// 	if (graph[parent[nbr]].a == nbr) j = 0;
					// 	else if (graph[parent[nbr]].b == nbr) j = 1;
					// 	else j = 2;
					// 	if (i < j) parent[nbr] = nid;
					// }
				}
			}
		}
		if (flag) break;
		for (int i = 0; i < nxt_border; ++i) 
			visit[(*nxt)[i]] = false;
		vector<int>* temp = cur;
		cur = nxt;
		nxt = temp;
		border_n = nxt_border;
	}
	// build path & print 
	fout << ssp[tnid] << endl;
	int pnid = tnid;
	string path = "";
	while (pnid != snid) {
		int nid = parent[pnid];
		if (graph[nid].a == pnid) path += "A";
		else if (graph[nid].b == pnid) path += "B";
		else path += "C";
		pnid = nid;
	}
	int cumu = 0;
	for (int i = ssp[tnid] - 1; i >= 0; --i) {
		fout << path[i];
		if (++cumu == 60) { 
			fout << endl;
			cumu = 0;
		}
	}
	if (cumu) fout << endl;
	// end
    fin.close();
    fout.close();
    return 0;
}

