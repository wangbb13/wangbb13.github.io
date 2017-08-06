#include <iostream>
using namespace std;

int main() {
  char letter[27] = {0};
  char ipt[26];
  int s, e, n;
  int i, j, k;
  cin >> s >> e >> n;
  for (i = 0; i < n; i++) {
    cin >> ipt[i];
  }
  for (i = 1; i < 27; i++) {
    letter[i] = ('a' + i - 1);
  }
  for (i = 0; i < 5; i++) {
    bool end = true;
    for (j = e, k = n-1; k >= 0; j--, k--) {
      if (letter[j] != ipt[k]) {
        end = false;
        break;
      }
    }
    if (end) {
      break;
    }
    for (j = n-1; j >= 0; j--) {
      if (ipt[j] < letter[e-(n-1-j)]) {
        break;
      }
    }
    ipt[j]++;
    for (j++; j < n; j++) {
      ipt[j] = ipt[j-1] + 1;
    }
    for (j = 0; j < n; j++) {
      cout << ipt[j];
    }
    cout << endl;
  }
  return 0;
}