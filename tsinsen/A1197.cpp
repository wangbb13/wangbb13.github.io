#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
  int p1, p2, p3;
  string str;
  int i, j, k, last_j;
  cin >> p1 >> p2 >> p3 >> str;
  i = 0; j = 0; last_j = 0;
  while (i < str.size()) {
    while (i < str.size() && str[i] != '-') { i++; }
    for (j = last_j; j < i-1; j++) {
      cout << str[j];
    }
    if ((i+1) < str.size() && i > 0) {
      if ((str[i+1] - str[i-1]) == 1) {
        if (last_j <= (i-1)) {
          cout << str[i-1];
        }
        cout<< str[i+1];
      } else if ((str[i+1] - str[i-1]) < 1 || (str[i+1] >= 'A' && str[i-1] <= '9') || str[i-1] == '-') {
        if (last_j <= (i-1)) {
          cout << str[i-1];
        }
        cout << str[i] << str[i+1];
      } else {
        if (last_j <= (i-1)) {
          cout << str[i-1];
        }
        if (p1 == 3) {
          for (j = 0; j < ((str[i+1] - str[i-1] - 1) * p2); j++) {
            cout << '*';
          }
        } else {
          string out_str = "";
          if (str[i-1] > '9') {
            char x = str[i-1];
            if (p1 == 1 && x < 'a') {
              x = x + 32;
            }
            if (p1 == 2 && x > 'Z') {
              x = x - 32;
            }
            for (j = 0; j < (str[i+1] - str[i-1] - 1); j++) {
              x = x + 1;
              for (k = 0; k < p2; k++) {
                out_str = out_str + x;
              }
            }
          } else {
            char x = str[i-1];
            for (j = 0; j < (str[i+1] - str[i-1] - 1); j++) {
              x = x + 1;
              for (k = 0; k < p2; k++) {
                out_str = out_str + x;
              }
            }
          }
          if (p3 == 1) {
            for (j = 0; j < out_str.size(); j++) {
              cout << out_str[j];
            }
          } else {
            for (j = (out_str.size() - 1); j > 0; j--) {
              cout << out_str[j];
            }
            cout << out_str[0];
          }
        }
        cout << str[i+1];
      }
      i += 2;
      last_j = i;
    } else {
      if (i == 0) {
        cout << str[i];
        i++;
        last_j = i;
        continue;
      }
      else {
        if (last_j <= (i-1)) {
          cout << str[i-1];
        }
        for (j = i; j < str.size(); j++) {
          cout << str[j];
        }
        break;
      }
    }
  }
  cout << endl;
  return 0;
}