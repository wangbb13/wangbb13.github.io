/*
ID: wangbb21
LANG: C++
TASK: friday
 */
#include <iostream>
#include <fstream>
using namespace std;

bool isLeap(int n) {
  return ((n % 400 == 0) || (n % 100 != 0 && n % 4 == 0));
}

int main() {
  ofstream fout("friday.out");
  ifstream fin("friday.in");
  int n, i, j, sy = 1900, no = 1;
  int month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int week[8] = {0};
  fin >> n;
  for (i = 0; i < n; i++) {
    if (isLeap(i+sy)) {
      month[1] = 29;
    } else {
      month[1] = 28;
    }
    no = (5 + no) > 7 ? (no-2) : (no+5);
    week[no]++;
    for (j = 0; j < 11; j++) {
      int x = no + (month[j] % 7);
      no = x > 7 ? (x - 7) : (x);
      week[no]++;
    }
    no = (5 + no) > 7 ? (no-2) : (no+5);
  }
  fout << week[6] << " " << week[7];
  for (i = 1; i < 6; i++) {
    fout << " " << week[i];
  }
  fout << endl;
  return 0;
}
