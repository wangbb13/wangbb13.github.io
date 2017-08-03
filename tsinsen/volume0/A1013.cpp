#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>


int main(int argc, char const *argv[]) 
{
  unsigned int result = 0;
  char input[8];
  int len;
  scanf("%s", input);
  len = strlen(input);
  for (int i = 0; i < len; i++) {
    char x = input[i];
    if (x >= '0' && x <= '9') {
      result = result * 16 + x - '0';
    } else if (x >= 'A' && x <= 'F') {
      result = result * 16 + x - 'A' + 10;
    }
  }
  printf("%u\n", result);
  system("pause");
  return 0;
}
