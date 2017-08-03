#include <iostream>
#include <string.h>
using namespace std;
int main () {
  char str[100], sub_str_0[100], sub_str_1[100];
  int max_replicate_len = 0;
  int str_len, remain_len;
  int i, j;
  memset(str, 0, 100);
  cin >> str;
  str_len = strlen(str);
  for (i = 0; i < str_len; i++) {
    remain_len = str_len - i;
    int loop = remain_len / 2;
    if (loop < max_replicate_len) {
      break;
    }
    for (j = 1; j <= loop; j++) {
      memset(sub_str_0, 0, 100);
      memset(sub_str_1, 0, 100);
      strncpy(sub_str_0, (str+i), j);
      strncpy(sub_str_1, (str+i+j), j);
      if (strcmp(sub_str_0, sub_str_1) == 0 && j > max_replicate_len) {
        max_replicate_len = j;
      }
    }
  }
  cout << max_replicate_len * 2 << endl;
}