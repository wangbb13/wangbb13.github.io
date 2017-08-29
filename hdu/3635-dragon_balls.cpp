#include <iostream>
#include <cstdlib>
using namespace std;

int us[10002] = {0};
int tr[10002] = {0};
int su[10002] = {0};

void init(int x) {
  for (int i = 1; i <= x; i++) {
    tr[i] = 0;
    us[i] = i;
    su[i] = 1;
  }
}

int find(int x) {
  while (us[x] != us[us[x]]) {
    tr[x] += tr[us[x]];
    us[x] = us[us[x]];
  }
  return us[x];
  
  // if (x == us[x]) {
  //   return x;
  // }
  // int temp = us[x];
  // us[x] = find(us[x]);
  // tr[x] += tr[temp];
  // return us[x];
}

// bring x to y
void merge(int x, int y) {
  int a = find(x), b = find(y);
  if (a != b) {
    us[a] = b;
    tr[a]++;
    su[b] += su[a];
    su[a] = 0;
  }
}

int main() {
  int T, n, q, i, j, a, b, c;
  char ch[5];
  cin >> T;
  j = 0;
  while (T--) {
    // cin >> n >> q;
    scanf("%d%d", &n, &q);
    j++;
    cout << "Case " << j << ":" << endl;
    init(n);
    for (i = 0; i < q; i++) {
      // cin >> ch;
      scanf("%s", &ch);
      if (ch[0] == 'T') {
        // cin >> a >> b;
        scanf("%d%d", &a, &b);
        merge(a, b);
      } else if (ch[0] == 'Q') {
        // cin >> a;
        scanf("%d", &a);
        c = find(a);
        printf("%d %d %d\n", c, su[c], tr[a]);
        // cout << c << " " << su[c] << " " << tr[a] << endl;
      }
    }
  }
  return 0;
}