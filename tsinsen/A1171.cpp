#include <iostream>
using namespace std;

typedef struct er {
  int no;
  int grade;
} ER;

int main() {
  ER list[5000];
  ER temp;
  int n, m, i, j, k;
  cin >> n >> m;
  for (i = 0; i < n; i++) {
    cin >> list[i].no >> list[i].grade;
  }
  for (i = 0; i < n-1; i++) {
    for (j = n-1; j > i; j--) {
      if (list[j].grade > list[j-1].grade || (list[j].grade == list[j-1].grade && list[j].no < list[j-1].no)) {
        temp = list[j];
        list[j] = list[j-1];
        list[j-1] = temp;
      }
    }
  }
  m = m * 1.5;
  k = list[m-1].grade;
  while (list[m].grade == list[m-1].grade) { m++; }
  cout << k << " " << m << endl;
  for (i = 0; i < m; i++) {
    cout << list[i].no << " "<< list[i].grade << endl;
  }
  return 0;
}