#include <iostream>
#include <vector>
using namespace std;

int n;
vector< vector<int> > set;

void deal2(int num, vector<int> array, int p, int sum) {
  int i, j;
  if (sum == n) {
    cout << n << "=";
    for (i = 0; array[i+1] != 0; i++) {
      cout << array[i] << "+";
    }
    cout << array[i] << endl;
    return;
  }
  for (j = 1; j <= num; j++) {
    array[p] = j;
    deal2((num-j), array, p+1, (sum+j));
    array[p] = 0;
  }
}

bool notIn(vector<int> a) {
  for (int i = 0; i < set.size(); i++) {
    if (set[i].size() == a.size()) {
      int t1[15] = {0};
      int t2[15] = {0};
      for (int j = 0; j < a.size(); j++) {
        t1[a[j]]++;
        t2[set[i][j]]++;
      }
      bool flag = true;
      for (int j = 0; j < 15; j++) {
        if (t1[j] != t2[j]) {
          flag = false;
          break;
        }
      }
      if (flag) {
        return false;
      }
    }
  }
  return true;
} 

void deal1(int num, vector<int> array, int p, int sum) {
  int i, j;
  if (sum == n) {
    if (notIn(array)) {
      set.push_back(array);
      cout << n << "=";
      for (i = 0; array[i+1] != 0; i++) {
        cout << array[i] << "+";
      }
      cout << array[i] << endl;
    }
    return;
  }
  for (j = 1; j <= num; j++) {
    array[p] = j;
    deal1((num-j), array, p+1, (sum+j));
    array[p] = 0;
  }
}

int main() {
  int m;
  int i, j, k;
  vector<int> array(15, 0);
  cin >> n >> m;
  if (m == 1) {
    deal2(n, array, 0, 0);
  }
  if (m == 2) {
    deal1(n, array, 0, 0);
  }
  return 0;
}