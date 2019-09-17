/*
ID: wangbb21
LANG: C++11
TASK: milk6
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 40;
const int M = 1010;
const int INF = 0x1fffffff;

int mat[N][N];
typedef struct __e {
	int u, v, w, eno, idx;
} _e;
vector<_e> edges(M);

int rec[N];
int flow[N];
int m_prev[N];
bool visit[M];
bool usage[M];
int path[M];

int prelim[M];
int aN, aM;

int f_max_flow() {
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
	return total_flow;
}

int main() {
    ofstream fout("milk6.out");
    ifstream fin("milk6.in");
    // read data 
	fin >> aN >> aM;
	int u, v, w;
	for (int i = 1; i <= aM; ++i) {
		fin >> u >> v >> w;
		mat[u][v] += w;
		edges[i].idx = i;
		edges[i].u = u;
		edges[i].v = v;
		edges[i].w = w;
		edges[i].eno = rec[u];
		rec[u] = i;
	}
	int ans_mf = f_max_flow();
	fout << ans_mf << " ";

	sort(edges.begin() + 1, edges.begin() + aM + 1, [](const _e& a, const _e& b) {
		return a.w > b.w;
	});
	int pli = 0, source = 1, sink = aN;
	for (int i = 1; i <= aM; ++i) usage[i] = true;
	for (int i = 1; i <= aM; ++i) {
		if (edges[i].w <= ans_mf) {
			for (int u = source; u <= sink; ++u) 
				for (int v = source; v <= sink; ++v) 
					mat[u][v] = 0;
			for (int x = 1; x <= aM; ++x) 
				if (usage[x] && (x != i))  
					mat[edges[x].u][edges[x].v] += edges[x].w;
			int one_ans = f_max_flow();
			if (one_ans + edges[i].w == ans_mf) {
				ans_mf = one_ans;
				usage[i] = false;
				path[pli++] = edges[i].idx;
			}
		}
		if (ans_mf == 0) break;
	}
	fout << pli << endl;
	sort(path, path + pli);
	for (int i = 0; i < pli; ++i) 
		fout << path[i] << endl;

    fin.close();
    fout.close();
    return 0;
}

