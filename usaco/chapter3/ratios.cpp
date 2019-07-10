/*
ID: wangbb21
LANG: C++
TASK: ratios
*/
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

typedef vector< vector<int> > mat2i;

int legal(mat2i& nums, int x, int y, int z) {
	int ans = -1;
	int as = x * nums[1][0] + y * nums[2][0] + z * nums[3][0];
	int bs = x * nums[1][1] + y * nums[2][1] + z * nums[3][1];
	int cs = x * nums[1][2] + y * nums[2][2] + z * nums[3][2];
	if (as * nums[0][1] == bs * nums[0][0] && 
		bs * nums[0][2] == cs * nums[0][1] && 
		as * nums[0][2] == cs * nums[0][0]) {
		if (as != 0 && nums[0][0] != 0) return as / nums[0][0];
		if (bs != 0 && nums[0][1] != 0) return bs / nums[0][1];
		if (cs != 0 && nums[0][2] != 0) return cs / nums[0][2];
		return ans;
	}
	return ans;
}

int main() {
    ofstream fout("ratios.out");
    ifstream fin("ratios.in");
    int min_sum = 300, a, b, c, d;
	a = b = c = d = 0;
	mat2i input(4, vector<int>(3));
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 3; ++j) {
			fin >> input[i][j];
		}
	}
	for (int x = 0; x < 100; ++x) {
		for (int y = 0; y < 100; ++y) {
			for (int z = 0; z < 100; ++z) {
				int gr = legal(input, x, y, z);
				if (gr > 0) {
					int sum = x + y + z;
					if (sum < min_sum) {
						min_sum = sum;
						a = x; b = y; c = z; d = gr;
					}
				}
			}
		}
	}
	if (min_sum == 300) fout << "NONE" << endl;
	else fout << a << " " << b << " " << c << " " << d << endl;
    fin.close();
    fout.close();
    return 0;
}

