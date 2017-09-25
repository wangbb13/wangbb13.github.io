#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct e {
  string dna;
  int inv, no;
} E;

bool cmp(E a, E b) {
  if (a.inv != b.inv) {
    return a.inv < b.inv; 
  }
  return a.no < b.no;
}

int main() {
  string str;
  int n, m, i, j, k, c, g, t;
  cin >> n >> m;
  vector<E> nums(m);
  k = 0;
  while (m--) {
    cin >> str;
    c = g = t = j = 0;
    for (i = 0; i < n; i++) {
      if (str[i] == 'A') {
        j += (c + g + t);
      } else if (str[i] == 'C') {
        j += (g + t);
        c++;
      } else if (str[i] == 'G') {
        j += t;
        g++;
      } else {
        t++;
      }
    }
    nums[k].dna = str;
    nums[k].inv = j;
    nums[k].no  = k;
    k++;
  }
  sort(nums.begin(), nums.end(), cmp);
  for (i = 0; i < k; i++) {
    cout << nums[i].dna << endl;
  }
  return 0;
}