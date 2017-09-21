#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
  double record[280] = {0.0};
  double input;
  for (int i = 1; i < 280; i++) {
    record[i] = record[i-1] + (double)(1 / (double)(i+1));
  }
  while (true) {
    cin >> input;
    if (input == 0) {
      break;
    }
    for (int i = 0; i < 280; i++) {
      if (record[i] <= input && input <= record[i+1]) {
        cout << (i+1) << " card(s)" << endl;
        break;
      }
    }
  }
  return 0;
}