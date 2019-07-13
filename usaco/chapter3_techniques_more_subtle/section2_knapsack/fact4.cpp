/*
ID: wangbb21
LANG: C++
TASK: fact4
 */
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream fout("fact4.out");
    ifstream fin("fact4.in");
    int n;
	fin >> n;
	int cnt = 0, tmp = n, ans = 1;
	while (tmp) {
		cnt += tmp / 5;
		tmp /= 5;
	}
	for (int i = 2; i <= n; ++i) {
		int j = i;
		while ((cnt > 0) && (j % 2 == 0)) {
			cnt--;
			j /= 2;
		}
		while (j % 5 == 0) {
			j /= 5;
		}
		ans = (ans * j) % 10;
	}
	fout << ans << endl;
	fin.close();
	fout.close();
    return 0;
}
