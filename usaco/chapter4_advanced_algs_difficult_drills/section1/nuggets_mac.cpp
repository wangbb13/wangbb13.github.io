/*
ID: wangbb21
LANG: C++
TASK: nuggets
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 257;
const int U = 1e7;
bool access[N];

inline int m_add(int a, int b) {	// a + b
	return (a + b) % N;
}

inline int m_minus(int a, int b) {	// a - b
	return (a + N - b) % N;
}

int main() {
    ofstream fout("nuggets.out");
    ifstream fin("nuggets.in");
	int n; fin >> n;
	vector<int> input(n);
	for (int i = 0; i < n; ++i) {
		fin >> input[i];
		access[input[i]] = true;
	}
	sort(input.begin(), input.end());
	if (input[0] == 1 || n == 1) {
		fout << 0 << endl;
		fin.close(); fout.close();
		return 0;
	}
	int ln = input[0], ll = 1, an = 0, al = 0;
	bool flag = false, find = false;
	for (int i = input[0]; i <= U; ++i) {
		int ti = m_add(0, i);
		if (i > 256) access[ti] = false;
		if (!access[ti]) {
			for (int j = 0; j < n; ++j) {
				if (i < input[j]) continue;
				int tk = m_minus(ti, input[j]);
				if (access[tk]) {
					access[ti] = true;
					break;
				}
			}
		}
		if (access[ti]) {
			if (flag) {
				al++;
			} else { 
				an = i; 
				al = 1; 
				flag = true;
			}
		} else {
			if (flag) {
				ln = an;
				ll = al;
				flag = false;
			}
		}
		if (al == input[0]) {
			fout << an - 1 << endl;
			find = true;
			break;
		}
	}
	if (!find) fout << 0 << endl;
    fin.close();
    fout.close();
    return 0;
}

