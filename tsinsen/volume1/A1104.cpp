#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) 
{
  int a1, a2, a3, a5, a10, a20;
  int total = 0;
  char record[1001];
  for (int i = 0; i < 1001; i++) {
    record[i] = 0;
  }
  cin >> a1 >> a2 >> a3 >> a5 >> a10 >> a20;
  for (int i = 0; i <= a1; i++) {
    for (int j = 0; j <= a2; j++) {
      for (int k = 0; k <= a3; k++) {
        for (int m = 0; m <= a5; m++) {
          for (int n = 0; n <= a10; n++) {
            for (int o = 0; o <= a20; o++) {
              int cr = i*1 + j*2 + k*3 + m*5 + n*10 + o*20;
              if (record[cr] == 0 && cr > 0) {
                record[cr] = 1;
                total++;
              }
            }
          }
        }
      }
    }
  }
  cout << "Total=" << total << endl;
  system("pause");
  return 0;
}
