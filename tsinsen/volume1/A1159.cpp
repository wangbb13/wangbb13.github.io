#include <iostream>
using namespace std;

typedef struct stu {
  int x, y, z;
} Std;

bool lesss(Std a, Std b) {
  return (a.x < b.x || (a.x == b.x && a.y < b.y) || (a.x == b.x && a.y == b.y && a.z > b.z));
}

int main() {
  Std list[301];
  int n, i, j, k;
  int x, y, z;
  cin >> n;
  for (i = 1; i <= n; i++) {
    cin >> x >> y >> z;
    list[i].x = (x + y + z);
    list[i].y = x;
    list[i].z = i;
  }
  for (i = 1; i < n; i++) {
    for (j = n; j > i; j--) {
      if (!lesss(list[j], list[j-1])) {
        Std tm = list[j];
        list[j] = list[j-1];
        list[j-1] = tm;
      }
    }
  }
  for (i = 1; i < 6; i++) {
    cout << list[i].z << " " << list[i].x << endl;
  }
  return 0;
}