#include <iostream>
using namespace std;

int binarySearch(int *array, int n, int tag) {
  int l = 0, r = n;
  int mid;
  while (l < r) {
    mid = (l + r) / 2;
    if (array[mid] == tag) {
      return mid;
    } else if (array[mid] < tag) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  if (l == r) {
    if (array[r] >= tag) { return r; }
    else { return r+1; }
  } else {
    return l;
  }
}

int main(int argc, char const *argv[])
{
  int number[10003] = {0};
  int count[10003] = {0};
  int n, m = 0, a;
  int i, j, pos;
  cin >> n;
  cin >> a;
  number[0] = a;
  count[0] = 1;
  for (i = 1; i < n; i++) {
    cin >> a;
    pos = binarySearch(number, m, a);
    if (number[pos] == a) {
      count[pos]++;
    } else {
      m++;
      for (j = m; j > pos; j--) {
        number[j] = number[j-1];
        count[j] = count[j-1];
      }
      number[pos] = a;
      count[pos] = 1;
    }
  }
  for (i = 0; i <= m; i++) {
    cout << number[i] << " " << count[i] << endl;
  }
  return 0;
}