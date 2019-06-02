/**
 * Description: IOI 1994 Number Triangles 
 * Input : N \n triangular matrix
 * Output: maximum sum 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int R, ans = 0;
	cin >> R;
	vector< vector<int> > mat(R, vector<int>(R, 0));
	for (int i = 0; i < R; ++i) 
		for (int j = 0; j < i + 1; ++j) 
			cin >> mat[i][j];
	for (int i = 1; i < R; ++i) {
		mat[i][0] += mat[i - 1][0];
		for (int j = 1; j < i; ++j) 
			mat[i][j] += max(mat[i - 1][j], mat[i - 1][j - 1]);
		mat[i][i] += mat[i - 1][i - 1];
	}
	for (int i = 0; i < R; ++i) 
		ans = max(ans, mat[R - 1][i]);
	cout << ans << endl;
    return 0;
}

