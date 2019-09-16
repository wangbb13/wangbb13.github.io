/*
ID: wangbb21
LANG: C++11
TASK: milk6
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

const int N = 40;
const int M = 1010;
const int INF = 0x1fffffff;

int mat[N][N];
struct __e {
	int u, v, w, eno;
} edges[M];
int rec[N];
int flow[N];
int m_prev[N];
bool visit[M];
bool reach[M];

int prelim[M];
int aN, aM;

void dfs(int nid) {
	reach[nid] = true;
	int eno = rec[nid];
	for (int j = eno; j; j = edges[j].eno) {
		if (!visit[j]) continue;
		int vid = edges[j].v;
		if (reach[vid]) continue;
		dfs(vid);
	}
}

int main() {
    ofstream fout("milk6.out");
    ifstream fin("milk6.in");
    // read data 
	fin >> aN >> aM;
	int u, v, w;
	for (int i = 1; i <= aM; ++i) {
		fin >> u >> v >> w;
		mat[u][v] = w;
		edges[i].u = u;
		edges[i].v = v;
		edges[i].w = w;
		edges[i].eno = rec[u];
		rec[u] = i;
	}
	// maximum flow | minimum cut 
	int total_flow = 0, source = 1, sink = aN;
	int max_val, max_loc;
	while (true) {
		for (int i = source; i <= sink; ++i) {
			flow[i] = 0;
			m_prev[i] = 0;
			visit[i] = false;
		}
		flow[source] = INF;
		max_val = max_loc = 0;
		while (true) {
			max_val = max_loc = 0;
			for (int i = source; i <= sink; ++i) {
				if (!visit[i] && max_val < flow[i]) {
					max_val = flow[i];
					max_loc = i;
				}
			}
			if (max_loc == 0 || max_loc == sink) break;
			visit[max_loc] = true;
			for (int nbr = source; nbr <= sink; ++nbr) {
				if (mat[max_loc][nbr] == 0) continue;
				int min_x = min(max_val, mat[max_loc][nbr]);
				if (flow[nbr] < min_x) {
					flow[nbr] = min_x;
					m_prev[nbr] = max_loc;
				}
			}
		}
		if (max_loc == 0) break;
		total_flow += flow[sink];
		int pid;
		while (max_loc != source) {
			pid = m_prev[max_loc];
			mat[pid][max_loc] -= flow[sink];
			mat[max_loc][pid] += flow[sink];
			max_loc = pid;
		}
	}
	fout << total_flow << " ";
	// get indexes of edges 
	int pi = 0, T = 0;
	for (int i = 1; i <= aM; ++i) {
		visit[i] = true;
		if (mat[edges[i].u][edges[i].v] == 0) {
			prelim[pi++] = i;
			visit[i] = false;
		}
	}

	T = pi;
	for (int j = pi - 1; j >= 0; --j) {
		int ei = prelim[j];
		visit[ei] = true;
		for (int i = source; i <= sink; ++i) reach[i] = false;
		dfs(source);
		if (!reach[sink]) {
			T--;
			prelim[j] = 0;
			visit[ei] = true;
		} else {
			visit[ei] = false;
		}
	}
	fout << T << endl;
	for (int i = 0; i < pi; ++i) {
		if (prelim[i]) fout << prelim[i] << endl;
	}
    fin.close();
    fout.close();
    return 0;
}

