#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef struct bigInt {
  int digits[20];
  int size;
} BigInt;

typedef struct a {
  int x, y;
  a() {
    x = -1;
    y = -1;
  }
} A;

int main() {
  // BigInt a = {{0}, 0};
  // cout << a.size << endl;
  // for (int i = 0; i < 20; i++) {
  //   cout << a.digits[i] << " ";
  // }
  // cout << endl;
  // A t[10];
  // for (int i = 0; i < 10; i++) {
  //   cout << t[i].x << " " << t[i].y << endl;
  // }
  char ch[10];
  for (int i = 0; i < 4; i++) {
    cin >> ch[i];
  }
  for (int i = 0; i < 4; i++) {
    cout << ch[i];
  }
  return 0;
}
