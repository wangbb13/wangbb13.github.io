/*
 * TITLE: To The Max
 * KEYWORD: Matrix( N * N ) SubMatrix MaxSum
 * KIND: DP ? 
 * RANGE: N <= 100, element <- [-127, 127]
 */

#include <iostream>
#include <climits>
using namespace std;

int subMax(int* array, int n) {
  int thisSum = 0, maxSum = INT_MIN;
  for (int i = 0; i < n; i++) {
    thisSum += array[i];
    if (thisSum > maxSum) {
      maxSum = thisSum;
    } else if (thisSum < 0) {
      thisSum  = 0;
    }
  }
  return maxSum;
}

int main(int argc, char const *argv[])
{
  int matrix[101][101];
  int array[101];
  int N, i, j, k;
  int subMatrixSum = INT_MIN, rSum;
  cin >> N;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      cin >> matrix[i][j];
    }
  }
  for (i = 0; i < N; i++) {
    for (k = 0; k < N; k++) {
      array[k] = 0;
    }
    for (j = i; j < N; j++) {
      for (k = 0; k < N; k++) {
        array[k] += matrix[j][k];
      }
      rSum = subMax(array, N);
      if (rSum > subMatrixSum) {
        subMatrixSum = rSum;
      }
    }
  }
  cout << subMatrixSum << endl;
  system("pause");
  return 0;
}