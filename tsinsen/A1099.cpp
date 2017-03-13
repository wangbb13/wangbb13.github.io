#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

char Week2Char(char *s) {
  if (!strncmp(s, "monday", 6)) {
    return 1;
  } else if (!strncmp(s, "tuesday", 7)) {
    return 2;
  } else if (!strncmp(s, "wednesday", 9)) {
    return 4;
  } else if (!strncmp(s, "thursday", 8)) {
    return 8;
  } else if (!strncmp(s, "friday", 6)) {
    return 16;
  } else if (!strncmp(s, "saturday", 8)) {
    return 32;
  } else if (!strncmp(s, "sunday", 6)) {
    return 64;
  } else {
    printf("undefined\n");
  }
}

void ShowResult(int i) {
  switch (i) {
    case 0:
      printf("Monday\n");
      break;
    case 1:
      printf("Tuesday\n");
      break;
    case 2:
      printf("Wednesday\n");
      break;
    case 3:
      printf("Thursday\n");
      break;
    case 4:
      printf("Friday\n");
      break;
    case 5:
      printf("Saturday\n");
      break;
    case 6:
      printf("Sunday\n");
      break;
    default:
      printf("Not in range.\n");
      break;
  }
}

void ToLower(char* s) {
  char x = 1 << 5;
  while(*s != 0) {
    *s |= x;
    s++;
  }
}

int main(int argc, char const *argv[]) 
{
  char describe[8][2];
  char input[20];
  char test;
  int flag;
  for (int i = 0; i < 8; i++) {
    scanf("%s", input);
    ToLower(input);
    describe[i][0] = Week2Char(input);
    scanf("%s", input);
    ToLower(input);
    describe[i][1] = ~Week2Char(input);
  }
  for (int i = 0; i < 7; i++) {
    test = 1 << i;
    flag = 1;
    for (int j = 0; j < 8; j++) {
      flag = flag && ((test & describe[j][0]) ^ (test & describe[j][1]));
    }
    if (flag) {
      ShowResult(i);
      break;
    }
  }
  system("pause");
  return 0;
}
