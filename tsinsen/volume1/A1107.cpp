#include <iostream>
using namespace std;

int matrix[64][64];

int main() {
  int n, i, j, k;
  cin >> n;
  n = 1 << n;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      matrix[i][j] = 0;
    }
  }
  for (i = 1; i < n; i++) {
    int bitmap[64] = {0};
    int count = 2;
    bitmap[0] = 1;
    bitmap[i] = 1;
    matrix[0][i] = 1;
    matrix[i][0] = 1;
    cout << "<" << i << ">" << 1 << "-" << (i+1);
    while (count < n-2) {
      for (j = 1; j < n; j++) {
        if (bitmap[j] == 0) {
          break;
        }
      }
      for (k = j+1; k < n; k++) {
        if (bitmap[k] == 0 && matrix[j][k] == 0) {
          matrix[j][k] = 1;
          matrix[k][j] = 1;
          bitmap[j] = 1;
          bitmap[k] = 1;
          count += 2;
          cout << "," << (j+1) << "-" << (k+1);
          break;
        }
      }
    }
    for (j = 1; j < n; j++) {
      if (bitmap[j] == 0) {
        break;
      }
    }
    for (k = j+1; k < n; k++) {
      if (bitmap[k] == 0 && matrix[j][k] == 0) {
        matrix[j][k] = 1;
        matrix[k][j] = 1;
        cout << "," << (j+1) << "-" << (k+1) << endl;
        break;
      }
    }
  }
  return 0;
}