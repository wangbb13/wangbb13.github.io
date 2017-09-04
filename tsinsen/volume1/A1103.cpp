#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

// 思路要清晰再下手，简单明了为最佳

int main(int argc, char const *argv[]) 
{
  int n, i, j, k;
  int record[17][17];
  int flag[17];
  cin >> n;
  n = pow(2, n);
  memset(flag, 0, sizeof(flag));
  memset(record, 0, sizeof(record));
  for (i = 1; i < n; i++) {
    cout << "<" << i << ">";
    for (j = 1; j <= n; j++) {
      if (!flag[j]) {
        for (k = j + 1; k <= n; k++) {
          if (!flag[k] && !record[j][k] && !record[k][j]) {
            flag[k] = 1;
            record[j][k] = record[k][j] = 1;
            cout << j << "-" << k << " ";
            break;
          }
        }
      }
    }
    cout << endl;
    memset(flag, 0, sizeof(flag));
  }

  // for (i = 0; i < 16; i++) {
  //   for (j = 0 ; j < 16; j++) {
  //     record[i][j] = 0;
  //   }
  // }
  // for (i = 0; i < n; i++) {
  //   record[i][i] = 1;
  // }
  // for (i = 0; i < n-1; i++) {
  //   for (j = 0; j < n; j++) {
  //     trace[j] = 0;
  //   }
  //   cout << "<" << i+1 << ">";
  //   for (l = 0; l < n/2; l++) {
  //     // find a
  //     for (j = 0; j < n; j++) {
  //       int sum = 0;
  //       for (k = 0; k < n; k++) {
  //         sum += record[j][k];
  //       }
  //       if (sum == (i+1)) {
  //         a = j;
  //         trace[a] = 1;
  //         break;
  //       }
  //     }
  //     // find b
  //     for (j = 0; j < n; j++) {
  //       if (trace[j] == 0 && record[a][j] == 0) {
  //         b = j;
  //         trace[b] = 1;
  //         break;
  //       }
  //     }
  //     record[a][b] = 1;
  //     record[b][a] = 1;
  //     cout << a+1 << "-" << b+1 << " ";
  //   }
  //   cout << endl;
  // }
  // system("pause");
  return 0;
}
