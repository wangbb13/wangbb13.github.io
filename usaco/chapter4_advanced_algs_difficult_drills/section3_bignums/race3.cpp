/*
ID: wangbb21
LANG: C++11
TASK: race3
*/
#include <iostream>
#include <fstream>
using namespace std;

const int N = 51;
const int M = 101;

int loc[N], tgt[M];
bool ans1[N], ans2[N];
bool visit[N];

void clear(int n) {
	for (int i = 0; i < n; ++i) visit[i] = false;
}

void dfs(int si, int omit) {
	visit[si] = true;
	for (int i = loc[si]; i < loc[si + 1]; ++i) 
		if (tgt[i] != omit && !visit[tgt[i]]) 
			dfs(tgt[i], omit);
}

int main() {
    ofstream fout("race3.out");
    ifstream fin("race3.in");
    int ni = 1, ei = 0, ep;
	loc[0] = 0;
	while (true) {
		fin >> ep;
		if (ep == -2) loc[ni++] = ei;
		else if (ep == -1) break;
		else tgt[ei++] = ep;
	}
	ni--;
	int fn = 0, sn = 0;
	for (int i = 1; i < ni - 1; ++i) {
		clear(ni);
		dfs(0, i);
		if (visit[ni - 1]) continue;
		ans1[i] = true; fn++;
		bool flag = false;
		for (int j = 1; j < ni; ++j) {
			if (!visit[j]) {
				for (int k = loc[j]; k < loc[j + 1]; ++k) {
					if (visit[tgt[k]]) {
						flag = true;
						break;
					}
				}
				if (flag) break;
			}
		}
		if (flag) continue;
		ans2[i] = true; sn++;
	}
	fout << fn;
	for (int i = 0; i < ni; ++i) 
		if (ans1[i]) fout << " " << i;
	fout << endl;
	fout << sn;
	for (int i = 0; i < ni; ++i) 
		if (ans2[i]) fout << " " << i;
	fout << endl;
    fin.close();
    fout.close();
    return 0;
}

