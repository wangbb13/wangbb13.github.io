#include <iostream>
using namespace std;

typedef struct pair {
  int a, b;
} Pair;

int main() {
  Pair get_on[21], get_off[21], total[21];
  int a, n, m, x, y;
  cin >> a >> n >> m >> x;
  if (n < 4) {
    cout << a << endl;
    return 0;
  }
  get_on[1].a = 1;
  get_on[1].b = 0;
  get_on[2].a = 0;
  get_on[2].b = 1;
  get_off[1].a = 0;
  get_off[1].b = 0;
  get_off[2].a = 0;
  get_off[2].b = 1;
  total[1].a = 1;
  total[1].b = 0;
  total[2].a = 1;
  total[2].b = 0;
  for (int i = 3; i < n; i++) {
    get_on[i].a = get_on[i-1].a + get_on[i-2].a;
    get_on[i].b = get_on[i-1].b + get_on[i-2].b;
    get_off[i].a = get_on[i-1].a;
    get_off[i].b = get_on[i-1].b;
    total[i].a = total[i-1].a + get_on[i].a - get_off[i].a;
    total[i].b = total[i-1].b + get_on[i].b - get_off[i].b;
  }
  y = (m - total[n-1].a * a) / total[n-1].b;
  cout << (total[x].a * a + total[x].b * y) << endl;
  return 0;
}