/*
ID: wangbb21
LANG: C++
TASK: fence
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int N = 502;
const int E = 1030;

int main() {
    ofstream fout("fence.out");
    ifstream fin("fence.in");
	stack<int> m_stack;
    vector<int> path(E, 0);
	int path_i = 0;
	vector< vector<int> > adj(N);
	int F, a, b, mxn = 0;
	fin >> F;
	for (int i = 0; i < F; ++i) {
		fin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
		mxn = max(max(a, b), mxn);
	}
	// sort 
	for (int i = 1; i <= mxn; ++i) 
		sort(adj[i].begin(), adj[i].end());
	// find start node
	int start_n = 1;
	for (int i = 1; i <= mxn; ++i) {
		if (adj[i].size() % 2 == 1) {
			start_n = i;
			break;
		}
	}
	// find euler path
	m_stack.push(start_n);
	while (!m_stack.empty()) {
		int nid = m_stack.top();
		if (adj[nid].size() == 0) {
			path[path_i++] = nid;
			m_stack.pop();
		} else {
			int xid = adj[nid][0];
			adj[nid].erase(adj[nid].begin());
			adj[xid].erase(std::find(adj[xid].begin(), adj[xid].end(), nid));
			m_stack.push(xid);
		}
	}
	for (int i = path_i - 1; i >= 0; --i) 
		fout << path[i] << endl;
    fin.close();
    fout.close();
    return 0;
}

