/*
 * Title: Little Shop Of Flowers
 * Input: F V
 *        M: F rows V columns
 * Ouput: maxVal
 * Range: F <- [1, 100]
 *        V <- [F, 100]
 *        e <- [-50, 50]
 * maxVal = sum(M_1j1, M_2j2, ... , M_FjF)
 *          where j1 < j2 < ... < jF
 */
#include <iostream>
#include <climits>
using namespace std;

int matrix[101][101];
int record[101][101];
int F, V;

int subSum(int row, int bPos) {
  if (row == F) {
    return 0;
  }
  if (record[row][bPos] != 10000) {
    return record[row][bPos];
  }
  int maxSum = INT_MIN, rVal;
  for (int i = bPos; i <= (V - F + row); i++) {
    rVal = matrix[row][i] + subSum(row+1, i+1);
    if (rVal > maxSum) {
      maxSum = rVal;
    }
  }
  record[row][bPos] = maxSum;
  return maxSum;
}

int main(int argc, char const *argv[])
{  
  int i, j;
  cin >> F >> V;
  for (i = 0; i < F; i++) {
    for (j = 0; j < V; j++) {
      cin >> matrix[i][j];
    }
  }
  for (i = 0; i < 101; i++) {
    for (j = 0; j < 101; j++) {
      record[i][j] = 10000;
    }
  }
  cout << subSum(0, 0) << endl;
  system("pause");
  return 0;
}