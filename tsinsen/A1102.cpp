#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) 
{
  char input[43];
  char cmd, a1, a2;
  int len = 0;
  while (1) {
    scanf("%c", &input[len]);
    if (input[len] == '.') {
      input[++len] = 0;
      break;
    }
    len++;
  }
  scanf("%c", &cmd);
  scanf("%c", &cmd);
  if (cmd == 'D') {
    int i = 0;
    scanf("%c", &a1);
    scanf("%c", &a1);
    while (i < len && input[i] != a1) { 
      printf("%c", input[i]);
      i++;
    }
    i++;
    while (i < len) {
      printf("%c", input[i]);
      i++;
    }
    printf("\n");
  } else if (cmd == 'I') {
    int j = len-1;
    scanf("%c", &a1);scanf("%c", &a1);
    scanf("%c", &a2);scanf("%c", &a2);
    while (j >= 0 && input[j] != a1) { j--; }
    if (j < 0) {
      printf("%s\n", input);
    } else {
      int i = 0;
      while (i < j) { printf("%c", input[i]); i++; }
      printf("%c", a2);
      while (i < len) { printf("%c", input[i]); i++; }
      printf("\n");
    }
  } else if (cmd == 'R') {
    scanf("%c", &a1);scanf("%c", &a1);
    scanf("%c", &a2);scanf("%c", &a2);
    for (int i = 0; i < len; i++) {
      if (input[i] == a1) {
        printf("%c", a2);
      } else {
        printf("%c", input[i]);
      }
    }
    printf("\n");
  }
  system("pause");
  return 0;
}
