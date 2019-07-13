/*
ID: wangbb21
LANG: C++
TASK: butter
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

const int inf = 0xffffff;
typedef vector< vector<int> > mat2i;
typedef vector< unordered_set<int> > Adj;

void dijkstra(mat2i& mat, Adj& adj, int p, mat2i& dist) {
	size_t len = mat.size();
	dist[p][p] = 0;
	vector<bool> visit(len, true);
	visit[p] = false;
	vector<int> gray = vector<int>(len, 0);
	gray[0] = p;
	int found = 1;
	int bound = len - 1;
	unordered_set<int>::iterator it;
	while (true) {
		int next_f = found;
		bool flag = true;
		for (int i = 0; i < found; ++i) {
			int nid = gray[i];
			for (it = adj[nid].begin(); it != adj[nid].end(); ++it) {
				int tid = *it;
				if (visit[tid]) { 
					gray[next_f++] = tid;
					visit[tid] = false;
				}
				if (dist[p][nid] + mat[nid][tid] < dist[p][tid]) { 
					dist[p][tid] = dist[p][nid] + mat[nid][tid];
					flag = false;
				}
			}
		}
		found = next_f;
		if (flag) break;
	}
}

int main() {
    ofstream fout("butter.out");
    ifstream fin("butter.in");
    int N, P, C, ans = 0x2fffffff;
	fin >> N >> P >> C;
	mat2i pasture(P + 1, vector<int>(P + 1, inf));
	Adj adj(P + 1);
	vector<int> cow(N + 1);
	for (int i = 1; i <= N; ++i) 
		fin >> cow[i];
	int sp, tp, wp;
	for (int i = 0; i < C; ++i) {
		fin >> sp >> tp >> wp;
		pasture[sp][tp] = pasture[tp][sp] = wp;
		adj[sp].insert(tp);
		adj[tp].insert(sp);
	}
	mat2i dist(P + 1, vector<int>(P + 1, inf));
	for (int i = 1; i <= N; ++i) 
		dijkstra(pasture, adj, cow[i], dist);
	for (int i = 1; i <= P; ++i) {
		int one = 0;
		for (int j = 1; j <= N; ++j) 
			one += dist[cow[j]][i];
		ans = min(ans, one);
	}
	fout << ans << endl;
    fin.close();
    fout.close();
    return 0;
}

