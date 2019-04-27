/**
 * Description: maximum sqaure
 * Input : n m \n the matrix of 0 or 1
 * Output: maximum length of the side of a square
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100;
int mat[N][N] = {0};

int main() {
    int n, m, ans = 0;
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> mat[i][j];
		}
	}
	int w, x, y;
	bool flag;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (mat[i][j] > 0) {
				w = mat[i][j];
				flag = false;
				while (true) {
					w++;
					if (!(i + w - 1 < n && j + w - 1 < m)) {
						break;
					}
					y = j + w - 1;
					for (x = i; x < i + w - 1; ++x) {
						if (mat[x][y] == 0) {
							flag = true;
							break;
						}
					}
					if (flag) 
						break;
					x = i + w - 1;
					for (y = j; y < j + w; ++y) {
						if (mat[x][y] == 0) {
							flag = true;
							break;
						}
					}
					if (flag) 
						break;
				}
				w--;
				ans = max(w, ans);
				for (x = i; x < i + w; ++x) {
					for (y = j; y < j + w; ++y) {
						mat[x][y] = max(mat[x][y], min(i + w - x, j + w - y));
					}
				}
			}
		}
	}
	cout << ans << endl;
    return 0;
}

