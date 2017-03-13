#include <stdio.h> 
#include <stdlib.h> 


int main(int argc, char const *argv[]) 
{
  char showHex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                      'A', 'B', 'C', 'D', 'E', 'F'};
  int a;
  char result[8];
  int index = 7;
  scanf("%d", &a);
  if (a == 0) {
    printf("0\n");
    system("pause");
    return 0;
  }
  while(a) {
    result[index--] = showHex[(a & 15)];
    a >>= 4;
  }
  for (index++; index < 8; index++) {
    printf("%c", result[index]);
  }
  printf("\n");
  system("pause");
  return 0;
}
