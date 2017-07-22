#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef struct bigInt {
  int digits[20];
  int size;
} BigInt;

int main() {
  BigInt a = {{0}, 0};
  cout << a.size << endl;
  for (int i = 0; i < 20; i++) {
    cout << a.digits[i] << " ";
  }
  cout << endl;
  return 0;
}
