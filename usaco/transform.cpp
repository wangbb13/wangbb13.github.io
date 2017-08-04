/*
ID: wangbb21
LANG: C++
TASK: transform
 */
#include <iostream>
#include <fstream>
using namespace std;

char bef[10][10], ref[10][10], af[10][10];
int N;

bool comp(char a[10][10], char b[10][10]) {
  int i, j;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (a[i][j] != b[i][j]) {
        return false;
      }
    }
  }
  return true;
}

bool rotate90(char a[10][10], char b[10][10]) {
  int i, j;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (a[i][j] != b[j][N-i-1]) {
        return false;
      }
    }
  }
  return true;
}

bool rotate180(char a[10][10], char b[10][10]) {
  int i, j;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (a[i][j] != b[N-i-1][N-j-1]) {
        return false;
      }
    }
  }
  return true;
}

bool rotate270(char a[10][10], char b[10][10]) {
  int i, j;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (a[i][j] != b[N-j-1][i]) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  ofstream fout("transform.out");
  ifstream fin("transform.in");
  int i, j;
  fin >> N;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      fin >> bef[i][j];
      ref[i][N-j-1] = bef[i][j];
    }
  }
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      fin >> af[i][j];
    }
  }
  if (rotate90(bef, af)) {
    fout << 1 << endl;
  } else if (rotate180(bef, af)) {
    fout << 2 << endl;
  } else if (rotate270(bef, af)) {
    fout << 3 << endl;
  } else if (comp(ref, af)) {
    fout << 4 << endl;
  } else if (comp(bef, af)) {
    fout << 6 << endl;
  } else if (rotate90(ref, af) || rotate180(ref, af) || rotate270(ref, af)) {
    fout << 5 << endl;
  } else {
    fout << 7 << endl;
  }
  return 0;
}
