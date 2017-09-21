/*
* description:
* the max downhill of a matrix
* input: matrix <- |R(m * n)
* m n
* content of the matrix
* scope:
* m, n <- [1, 100]
* matrix(i, j) <- [0, 10000]
* output: the max length of the downhill
* solution:
* simple recursion
*/
#include <stdio.h>
#include <stdlib.h>

/*
* input: matrix, m, n, px, py
* output: let (px, py) as the starting point
*         find the max length of the downhill
*/
int max_len_from_one_point(int matrix[100][100], int m, int n, int px, int py, int mem[100][100]) {
	int max_len = 1;
	int a[4] = {0, 0, -1, 1};
	int b[4] = {-1, 1, 0, 0};
	int i;
	if (mem[px][py] > 0) {
		return mem[px][py];
	}
	for (i = 0; i < 4; i++) {
		int tx = px + a[i];
		int ty = py + b[i];
		if (tx >= 0 && tx < m && ty >=0 && ty < n) {
			if (matrix[px][py] > matrix[tx][ty]) {
				int max_t = 1 + max_len_from_one_point(matrix, m, n, tx, ty, mem);
				if (max_len < max_t) {
					max_len = max_t;
					mem[px][py] = max_len;
				}
			}
		}
	}
	return max_len;
}

int main(int argc, char const *argv[])
{
	int m, n, i, j, max = 1;
	int matrix[100][100];
	int mem[100][100];
	scanf("%d", &m);
	scanf("%d", &n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &matrix[i][j]);
			mem[i][j] = 0;
		}
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			int max_t = max_len_from_one_point(matrix, m, n, i, j, mem);
			if (max_t > max) {
				max = max_t;
			}
		}
	}
	printf("%d\n", max);
	getchar();
	getchar();
	return 0;
}
