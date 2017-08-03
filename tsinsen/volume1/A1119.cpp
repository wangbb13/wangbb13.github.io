#include <iostream>
#include <cstring>
using namespace std;

int main() {
  int al[26] = {0};
  int n, i, j, k;
  char in[5], ch;
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> in;
  }
  for (i = 1; i < n; i++) {
    cin >> ch;
    k = 0;
    for (j = 1; j < n; j++) {
      cin >> in;
      if (strlen(in) > 1) {
        k++;
      }
    }
    al[ch-'A'] = k+1;
  }
  for (i = 0; i < 26; i++) {
    if (al[i] > 0) {
      cout << (char)('A'+i) << "=" << al[i]-1 << " ";
    }
  }
  cout << endl << n-1 << endl;
  return 0;
}

/**
5
+ L K V E
L L K V E
K K V E KL
V V E KL KK
E E KL KK KV
**/
