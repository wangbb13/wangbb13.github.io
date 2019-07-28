/*
ID: wangbb21
LANG: C++
TASK: fence6
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
using namespace std;

const int N = 101;
int gmat[N][N];		// i -> j : -1 (left of j); 1 (right of j)
int weight[N];
int uset[N * 2];
int degree[N * 2];

int t_degree[N * 2];
int t_mat[N * 2][N * 2];

typedef vector< unordered_set<int> > ADJ;
ADJ t_adj;

void show_set(unordered_set<int>& us) {
	unordered_set<int>::iterator it;
	for (it = us.begin(); it != us.end(); ++it) 
		cout << *it << " ";
	cout << endl;
}

void dfs(int sid, int nid, unordered_set<int>& path, int pl, int& ans, int iter, int upper) {
	if (iter > upper) return;
	unordered_set<int>::iterator it;
	for (it = t_adj[nid].begin(); it != t_adj[nid].end(); ++it) {
		int nnid = *it;
		int edge = t_mat[nid][nnid];
		if (nnid == sid && path.size() > 2) {
			ans = min(ans, pl + edge);
			// if (ans > pl + edge) {
			// 	ans = pl + edge;
			// 	cout << ans << endl;
			// 	show_set(path);
			// }
			continue;
		}
		if (path.find(nnid) != path.end()) continue;
		path.insert(nnid);
		dfs(sid, nnid, path, pl + edge, ans, iter + 1, upper);
		path.erase(nnid);
	}
}

int main() {
    ofstream fout("fence6.out");
    ifstream fin("fence6.in");
    int n; fin >> n;
	int ans = 0;
	int n2 = n * 2;
	for (int i = 1; i <= n2; ++i) 
		uset[i] = i;
	int nid, ln, rn, nn, lnid, rnid;
	for (int i = 0; i < n; ++i) {
		fin >> nid;
		fin >> weight[nid] >> ln >> rn;
		ans += weight[nid];
		degree[2 * nid - 1] = ln + 1;
		degree[2 * nid] = rn + 1;
		for (int j = 0; j < ln; ++j) {
			fin >> nn;
			gmat[nn][nid] = -1;
		}
		for (int j = 0; j < rn; ++j) {
			fin >> nn;
			gmat[nn][nid] = 1;
		}
	}
	// transform
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (gmat[i][j] != 0) {
				if (gmat[i][j] == -1) lnid = j * 2 - 1;	// left of j
				else lnid = j * 2;	// right of j
				if (gmat[j][i] == -1) rnid = i * 2 - 1;	// left of i
				else rnid = i * 2;	// right of i
				uset[lnid] = min(uset[lnid], uset[rnid]);
				uset[rnid] = uset[lnid];
			}
		}
	}
	int tnid = 1;	// id: start from 1
	vector<int> t_map(n2 + 1, 0);
	int a, b, upper = 0;
	for (int i = 1; i < n2; i += 2) {
		a = uset[i];
		b = uset[i + 1];
		if (t_map[a] == 0) t_map[a] = tnid++;
		if (t_map[b] == 0) t_map[b] = tnid++;
		t_mat[t_map[a]][t_map[b]] = weight[(i + 1) / 2];
		t_mat[t_map[b]][t_map[a]] = t_mat[t_map[a]][t_map[b]];
		t_degree[t_map[a]] += degree[i];
		t_degree[t_map[b]] += degree[i + 1];
		upper = max(upper, max(t_degree[t_map[a]], t_degree[t_map[b]]));
		// adj
		if (t_adj.size() < tnid) t_adj.resize(tnid);
		// cout << "[" << t_map[a] << " <-> " << t_map[b] << "] : " << t_mat[t_map[a]][t_map[b]] << endl;
		t_adj[t_map[a]].insert(t_map[b]);
		t_adj[t_map[b]].insert(t_map[a]);
	}
	// DFS & result
	upper *= n;
	for (int i = 1; i < tnid; ++i) {
		unordered_set<int> path;
		path.insert(i);
		dfs(i, i, path, 0, ans, 0, upper);
	}
	fout << ans << endl;
    fin.close();
    fout.close();
    return 0;
}

