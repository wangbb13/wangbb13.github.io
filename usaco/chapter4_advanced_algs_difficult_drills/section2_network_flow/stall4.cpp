/*
ID: wangbb21
LANG: C++11
TASK: stall4
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

const int NM = 404;
const int INF = 0x1fffffff;
int mat[NM][NM];
int flow[NM];
int m_prev[NM];
bool visit[NM];
typedef vector< unordered_set<int> > ADJ;

int main() {
    ofstream fout("stall4.out");
    ifstream fin("stall4.in");
    // read bipartite graph
	int n, m; fin >> n >> m;
	int source = 1, sink = n + m + 2;
	ADJ adj(sink + 1);
	int ns, ni;
	n += 1;
	for (int i = 2; i <= n; ++i) {
		mat[source][i] = 1;
		adj[1].insert(i);
		fin >> ns;
		for (int j = 0; j < ns; ++j) {
			fin >> ni;
			ni += n;
			mat[i][ni] = 1;
			adj[i].insert(ni);
		}
	}
	for (int i = n + 1; i < sink; ++i) {
		mat[i][sink] = 1;
		adj[i].insert(sink);
	}
	// maximum flow alg
	int total_flow = 0;
	while (true) {
		// init
		for (int i = source; i <= sink; ++i) {
			flow[i] = 0;
			m_prev[i] = 0;
			visit[i] = false;
		}
		flow[source] = INF;
		// get an augmenting path
		int max_flow = 0, max_loc = 0;
		while (true) {
			max_flow = max_loc = 0;
			for (int i = source; i <= sink; ++i) {
				if (!visit[i] && flow[i] > max_flow) {
					max_flow = flow[i];
					max_loc = i;
				}
			}
			if (max_loc == 0 || max_loc == sink) break;
			visit[max_loc] = true;
			// adjust its neighbors
			for (const int& nid : adj[max_loc]) {
				int min_x = min(max_flow, mat[max_loc][nid]);
				if (flow[nid] < min_x) {
					flow[nid] = min_x;
					m_prev[nid] = max_loc;
				}
			}
		}
		// no augmenting path
		if (max_loc == 0) break;
		// adjust residual network
		total_flow += flow[sink];
		int pid;
		while (max_loc != source) {
			pid = m_prev[max_loc];
			mat[pid][max_loc] -= flow[sink];
			mat[max_loc][pid] += flow[sink];
			adj[max_loc].insert(pid);
			max_loc = pid;
		}
	}
	// result
	fout << total_flow << endl;
    return 0;
}
