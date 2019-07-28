/*
ID: wangbb21
LANG: C++
TASK: ditch
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
using namespace std;

#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

const int M = 201;
const int Inf = 0x1fffffff;
int mat[M][M];
int m_prev[M];
int flow[M];
bool visit[M];

typedef vector< unordered_set<int> > ADJ;

int main() {
    ofstream fout("ditch.out");
    ifstream fin("ditch.in");
    int n, m; fin >> n >> m;
	int s, e, c;
	ADJ adj(m + 1);
	for (int i = 0; i < n; ++i) {
		fin >> s >> e >> c;
		mat[s][e] += c;
		adj[s].insert(e);
	}
	int total_flow = 0;
	unordered_set<int>::iterator it;
	while (true) {
		// init
		for (int i = 1; i <= m; ++i) { 
			m_prev[i] = 0;
			flow[i] = 0;
			visit[i] = false;
		}
		flow[1] = Inf;
		// find a augmenting path
		int max_flow = 0, max_loc = 0;
		while (true) {
			max_flow = max_loc = 0;
			// bool first = true;
			for (int i = 1; i <= m; ++i) {
				// if (first && !visit[i] && flow[i] > 0) {
				// 	max_flow = flow[i];
				// 	max_loc = i;
				// 	first = false;
				// }
				if (!visit[i] && flow[i] > max_flow) {
					max_flow = flow[i];
					max_loc = i;
				}
			}
			// cout << "max_loc = " << max_loc << ", max_flow = " << max_flow << endl;
			if (max_loc == 0 || max_loc == m) break;
			visit[max_loc] = true;
			// adjust its neighbor
			for (it = adj[max_loc].begin(); it != adj[max_loc].end(); ++it) {
				int nid = *it;
				int min_x = min(max_flow, mat[max_loc][nid]);
				if (flow[nid] < min_x) {
					flow[nid] = min_x;
					m_prev[nid] = max_loc;
				}
			}
		}
		// cout << "max_loc = " << max_loc << ", total_flow += " << flow[m] << endl;
		// get a path
		if (max_loc == 0) break;
		total_flow += flow[m];
		// max_loc = m;
		while (max_loc != 1) {
			int next_nid = m_prev[max_loc];
			mat[next_nid][max_loc] -= flow[m];
			mat[max_loc][next_nid] += flow[m];
			adj[max_loc].insert(next_nid);
			max_loc = next_nid;
		}
	}
	fout << total_flow << endl;
    fin.close();
    fout.close();
    return 0;
}

