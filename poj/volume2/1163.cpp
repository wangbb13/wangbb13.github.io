/*
 * Title: The Triangle
 * Input: N
 *        N rows
 *        size of each row: 1, 2, ..., N
 * Output: maxSum for top to the end
 * Limit : each step can go either left or right
 * Range : N <- (1, 100]
 *         e <- [0, 99]
 */
#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char const *argv[])
{
  int matrix[101][101], dp[101][101];
  int N, i, j;
  cin >> N;
  for (i = 0; i < N; i++) {
    for (j = 0; j <= i; j++) {
      cin >> matrix[i][j];
    }
  }
  for (i = 0; i < N; i++) {
    dp[N-1][i] = matrix[N-1][i];
  }
  for (i = N-2; i >= 0; i--) {
    for (j = 0; j <= i; j++) {
      dp[i][j] = matrix[i][j] + max(dp[i+1][j], dp[i+1][j+1]);
    }
  }
  cout << dp[0][0] << endl;
  system("pause");
  return 0;
}