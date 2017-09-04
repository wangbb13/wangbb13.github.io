#include <iostream>
#include <vector>
using namespace std;

// 多重背包问题

int main(int argc, char const *argv[]) 
{
  int a[6];
  int b[6] = {1, 2, 3, 5, 10, 20};
  int total = 0;
  int record[1001] = {0};
  for (int i = 0; i < 6; i++) {
    cin >> a[i];
  }
  // for (int i = 0; i <= a1; i++) {
  //   for (int j = 0; j <= a2; j++) {
  //     for (int k = 0; k <= a3; k++) {
  //       for (int m = 0; m <= a5; m++) {
  //         for (int n = 0; n <= a10; n++) {
  //           for (int o = 0; o <= a20; o++) {
  //             int cr = i*1 + j*2 + k*3 + m*5 + n*10 + o*20;
  //             if (record[cr] == 0 && cr > 0) {
  //               record[cr] = 1;
  //               total++;
  //             }
  //           }
  //         }
  //       }
  //     }
  //   }
  // }
  record[0] = 1;
  for (int i = 0; i < 6; i++) {
    int k = 1, amount = a[i];
    if (amount == 0) {
      continue;
    }
    while (k < amount) {
      int w = k * b[i];
      for (int j = 1000; j >= w; j--) {
        if (record[j - w] == 1 && record[j] == 0) {
          record[j] = 1;
          total++;
        }
      }
      amount -= k;
      k *= 2;
    }
    int w = amount * b[i];
    for (int j = 1000; j >= w; j--) {
      if (record[j - w] == 1 && record[j] == 0) {
        record[j] = 1;
        total++;
      }
    }
  }
  cout << "Total=" << total << endl;
  // system("pause");
  return 0;
}