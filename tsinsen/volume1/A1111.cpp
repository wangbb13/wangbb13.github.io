#include <iostream>
using namespace std;

int ss[200] = {0};
int ssi = 0;
int matrix[101][101] = {0};
int map[10001] = {0};
bool lock = true;
int n, n2;

void generate() {
  int array[203] = {0};
  int i = 2, j;
  while (i < 200) {
    while (array[i] == 1) {
      i++;
    }
    ss[ssi++] = i;
    for (j = 2; i*j < 200; j++) {
      array[i*j] = 1;
    }
    i++;
  }
}

bool binSearch(int tag) {
  int l = 0, r = ssi-1;
  int mid;
  while (l < r) {
    mid = (l + r) / 2;
    if (ss[mid] == tag) {
      return true;
    } else if (ss[mid] < tag) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  if (l == r) {
    return ss[l] == tag;
  }
  return false;
}


void deal(int i, int j) {
  if (!lock) {
    return;
  }
  if (i == n-1 && j == n-1) {
    for (int x = 1; x <= n2; x++) {
      if (map[x] == 0) {
        matrix[i][j] = x;
        // cout << i << " " << j << "=" << x << endl;
        break;
      }
    }
    if (!(binSearch(matrix[i][j]+matrix[i-1][j]) && binSearch(matrix[i][j] + matrix[i][j-1]))) {
      return;
    }
    if (lock) {
      for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
          cout << matrix[x][y] << " ";
        }
        cout << endl;
      }
      lock = false;
    }
    return;
  }
  for (int x = 2; x <= n2; x++) {
    if (map[x] == 1) {
      continue;
    }
    if (i > 0) {
      if (!binSearch(matrix[i-1][j]+x)) {
        continue;
      }
    }
    if (j > 0) {
      if (!binSearch(matrix[i][j-1]+x)) {
        continue;
      }
    }
    matrix[i][j] = x;
    // cout << i << " " << j << "=" << x << endl;
    map[x] = 1;
    if (j+1 < n) {
      deal(i, j+1);
    } else {
      deal(i+1, 0);
    }
    map[x] = 0;
    matrix[i][j] = 0;
  }
}


int main() {
  cin >> n;
  if (n == 1) {
    cout << 1 << endl;
    return 0;
  }
  n2 = n * n;
  generate();
  matrix[0][0] = 1;
  map[1] = 1;
  deal(0, 1);
  if (lock) {
    cout << "NO" << endl;
  }
  return 0;
}