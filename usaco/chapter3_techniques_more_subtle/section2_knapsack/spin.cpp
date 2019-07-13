/*
ID: wangbb21
LANG: C++
TASK: spin
Solution: simplest, simulation on every angle
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

typedef struct _wheel {
	int speed;
	int wsn;
	vector< std::pair<int, int> > wedges;
} wheel;

int main() {
    ofstream fout("spin.out");
    ifstream fin("spin.in");
    vector<wheel> ws(5);
	int si, size;
	// read in
	for (int i = 0; i < 5; ++i) {
		fin >> ws[i].speed;
		fin >> ws[i].wsn;
		for (int j = 0; j < ws[i].wsn; ++j) {
			fin >> si >> size;
			ws[i].wedges.push_back(std::make_pair(si, size));
		}
	}
	// 360 iterations
	vector<int> its(360, -1);
	vector<int> record(360);
	int rec_num = 0;
	for (int i = 0; i < 360; ++i) {
		// init 
		rec_num = 0;
		for (int j = 0; j < ws[0].wsn; ++j) {
			record[rec_num++] = ws[0].wedges[j].first;
			its[record[rec_num - 1]] = ws[0].wedges[j].second;
		}
		// refine
		for (int j = 1; j < 5; ++j) {
			vector<int> next_its(360, -1);
			vector<int> next_rec(360);
			int next_num = 0;
			for (int k = 0; k < ws[j].wsn; ++k) {
				int si = ws[j].wedges[k].first;
				int so = ws[j].wedges[k].second;
				for (int r = 0; r < rec_num; ++r) {
					int oi = record[r];
					int os = its[oi];
					if (oi >= si && si + so >= oi) { // intersection
						int _os = min(os, si + so - oi);
						next_rec[next_num++] = oi;
						if (next_its[oi] == -1) 
							next_its[oi] = _os;
						else
							next_its[oi] = min(next_its[oi], _os);
					}
					if (si >= oi && oi + os >= si) {
						int _so = min(so, oi + os - si);
						next_rec[next_num++] = si;
						if (next_its[si] == -1)
							next_its[si] = _so;
						else
							next_its[si] = min(next_its[si], _so);
					}
					if (oi < si && (si + so >= 360) && ((si + so) % 360 >= oi)) {
						int _os = min(os, (si + so) % 360 - oi);
						next_rec[next_num++] = oi;
						if (next_its[oi] == -1) 
							next_its[oi] = _os;
						else
							next_its[oi] = min(next_its[oi], _os);
					}
					if (si < oi && (oi + os >= 360) && ((oi + os) % 360 >= si)) {
						int _so = min(so, (oi + os) % 360 - si);
						next_rec[next_num++] = si;
						if (next_its[si] == -1) 
							next_its[si] = _so;
						else
							next_its[si] = min(next_its[si], _so);
					}
				}
			}
			rec_num = next_num;
			if (next_num == 0) break;
			std::copy(next_rec.begin(), next_rec.end(), record.begin());
			std::copy(next_its.begin(), next_its.end(), its.begin());
		}
		if (rec_num > 0) {	// found
			fout << i << endl;
			fin.close();
			fout.close();
			return 0;
		}
		// spin 
		for (int j = 0; j < 5; ++j) {
			for (int k = 0; k < ws[j].wsn; ++k) {
				ws[j].wedges[k].first = (ws[j].wedges[k].first + ws[j].speed) % 360;
			}
		}
	}
	// none
	fout << "none" << endl;
    fin.close();
    fout.close();
    return 0;
}

