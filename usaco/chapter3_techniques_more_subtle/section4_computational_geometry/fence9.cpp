/*
ID: wangbb21
LANG: C++
TASK: fence9
*/
#include <iostream>
#include <fstream>
using namespace std;

int f_plus(int n, int m, int p) {
	int ans = 0, left, right, ip = p - n;
	double dn = n * 1.0, dm = m * 1.0, dp = ip * 1.0, dl, dr;
	for (int i = 1; i < m; ++i) {
		dl = i * 1.0 * dn / dm;
		left = (int)dl;
		if (i * n == m * left) left--;
		dr = i * 1.0 * dp / dm;
		right = (int)dr;
		if (i * ip == m * right) right--;
		ans += left + right + 1;
	}
	return ans;
}

int f_minus(int n, int m, int p) {
	int ans = 0, left, right, mid, ip = n - p;
	double dn = n * 1.0, dm = m * 1.0, dp = ip * 1.0, dl, dr;
	for (int i = 1; i < m; ++i) {
		dl = i * 1.0 * dn / dm;
		left = (int)dl;
		if (i * n == m * left) left--;
		dr = i * 1.0 * dp / dm;
		right = (int)dr;
		ans += (left - right);
	}
	return ans;
}

int main() {
    ofstream fout("fence9.out");
    ifstream fin("fence9.in");
    int n, m, p;
	fin >> n >> m >> p;
	if (p > n) fout << f_plus(n, m, p) << endl;
	else fout << f_minus(n, m, p) << endl;
    fin.close();
    fout.close();
    return 0;
}

