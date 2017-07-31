#include <iostream>
using namespace std;

int yu(int a) {
  if (a >= 0) {
    return (a % 10);
  } else {
    return (10-((-a) % 10)) % 10;
  }
}

int main() {
  int n, m;
  int in[51] = {0};
  int jz[51][51] = {0};
  int dp_max[51][10] = {0};
  int dp_min[51][10] = {0};
  int i, j, k;
  cin >> n >> m;
  for (i = 0; i < n; i++) {
    cin >> in[i];
  }
  for (i = 0; i < n; i++) {
    j = 1;
    jz[i][(i+j)%n] = yu(in[i]);
    for (j = 2; j < n; j++) {
      jz[i][(i+j)%n] = yu(jz[i][(i+j-1)%n] + in[(i+j-1)%n]);
    }
  }

}