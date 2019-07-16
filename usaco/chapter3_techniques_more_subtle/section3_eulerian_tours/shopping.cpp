/*
ID: wangbb21
LANG: C++
TASK: shopping
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int dp[6][6][6][6][6];
vector<int> code_map(1000, -1);
int cart[5][2];	// 0: # items; 1: price/item
int flag[5];	// 0: not in offer; 1: in offer

typedef struct _offer {
	int n, p;
	vector<int> cs;	// code
	vector<int> ks;	// # items
} offer; 

int mx_count(offer& of) {
	int ans = 10, idx;
	for (int i = 0; i < of.n; ++i) {
		idx = code_map[of.cs[i]];
		if (idx == -1) return -1;
		ans = min(ans, cart[idx][0] / of.ks[i]);
	}
	return ans;
}

int main() {
    ofstream fout("shopping.out");
    ifstream fin("shopping.in");
    int s, n, c, k, p, b, prod_i = 0;
	fin >> s;
	vector<offer> sp(s);
	for (int i = 0; i < s; ++i) {
		fin >> n; 
		sp[i].n = n;
		sp[i].cs.resize(n);
		sp[i].ks.resize(n);
		for (int j = 0; j < n; ++j) 
			fin >> sp[i].cs[j] >> sp[i].ks[j];
		fin >> sp[i].p;
	}
	fin >> b;
	for (int i = 0; i < b; ++i) {
		fin >> c >> k >> p;
		if (code_map[c] == -1) 
			code_map[c] = prod_i++;
		cart[code_map[c]][0] = k;
		cart[code_map[c]][1] = p;
	}
	// init dp
	vector< vector<int> > able_vec;
	vector<int> able_p;
	for (int i = 0; i < s; ++i) {
		int cnt = mx_count(sp[i]);
		if (cnt < 1) continue;
		vector<int> idc(5, 0);
		for (int j = 0; j < sp[i].n; ++j) {
			int code = code_map[sp[i].cs[j]];
			idc[code] = sp[i].ks[j];
			flag[code] = 1;
		}
		p = sp[i].p;
		able_vec.push_back(idc);
		able_p.push_back(p);
		// for (int j = 1; j <= cnt; ++j) {
		// 	int m = j - 1;
		// 	if (dp[idc[0] * j][idc[1] * j][idc[2] * j][idc[3] * j][idc[4] * j] == 0) 
		// 		dp[idc[0] * j][idc[1] * j][idc[2] * j][idc[3] * j][idc[4] * j] = p * j;
		// 	else 
		// 		dp[idc[0] * j][idc[1] * j][idc[2] * j][idc[3] * j][idc[4] * j] = min(
		// 			dp[idc[0] * j][idc[1] * j][idc[2] * j][idc[3] * j][idc[4] * j], 
		// 			dp[idc[0] * m][idc[1] * m][idc[2] * m][idc[3] * m][idc[4] * m] + p);
		// }
	}
	// dp
	int extra = 0;
	for (int i = 0; i < 5; ++i) {
		if (flag[i] == 0) {
			extra += cart[i][0] * cart[i][1];
			cart[i][0] = 0;
		}
	}
	int ax = cart[0][0], bx = cart[1][0], cx = cart[2][0], dx = cart[3][0], ex = cart[4][0];
	int pa = cart[0][1], pb = cart[1][1], pc = cart[2][1], pd = cart[3][1], pe = cart[4][1];
	for (int a = 0; a <= ax; ++a) {
		for (int b = 0; b <= bx; ++b) {
			for (int c = 0; c <= cx; ++c) {
				for (int d = 0; d <= dx; ++d) {
					for (int e = 0; e <= ex; ++e) {
						for (int stat = 1; stat < 32; ++stat) {
							int sa = ((stat & (1 << 4)) > 0);
							int sb = ((stat & (1 << 3)) > 0);
							int sc = ((stat & (1 << 2)) > 0);
							int sd = ((stat & (1 << 1)) > 0);
							int se = ((stat & 1) > 0);
							if ((a - sa < 0) || (b - sb < 0) || (c - sc < 0) || (d - sd < 0) || (e - se < 0)) continue;
							if (dp[a][b][c][d][e] == 0) {
								dp[a][b][c][d][e] = dp[a - sa][b - sb][c - sc][d - sd][e - se] + 
									sa * pa + sb * pb + sc * pc + sd * pd + se * pe;
							} else {
								dp[a][b][c][d][e] = min(dp[a][b][c][d][e], 
									dp[a - sa][b - sb][c - sc][d - sd][e - se] + 
									sa * pa + sb * pb + sc * pc + sd * pd + se * pe);
							}
						}
						for (int stat = 0; stat < able_p.size(); ++stat) {
							int sa = able_vec[stat][0];
							int sb = able_vec[stat][1];
							int sc = able_vec[stat][2];
							int sd = able_vec[stat][3];
							int se = able_vec[stat][4];
							if ((a - sa < 0) || (b - sb < 0) || (c - sc < 0) || (d - sd < 0) || (e - se < 0)) continue;
							if (dp[a][b][c][d][e] == 0) {
								dp[a][b][c][d][e] = dp[a - sa][b - sb][c - sc][d - sd][e - se] + able_p[stat];
							} else {
								dp[a][b][c][d][e] = min(dp[a][b][c][d][e], 
									dp[a - sa][b - sb][c - sc][d - sd][e - se] + able_p[stat]);
							}
						}
					}
				}
			}
		}
	}
	fout << dp[ax][bx][cx][dx][ex] + extra << endl;
    fin.close();
    fout.close();
    return 0;
}

