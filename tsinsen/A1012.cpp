#include <stdio.h> 
#include <stdlib.h> 


int main(int argc, char const *argv[]) 
{
  char result[32];
  int a, p, index = 31, x;
  scanf("%d", &a);
  scanf("%d", &p);
  if (a == 0) {
    printf("0\n");
    system("pause");
    return 0;
  }
  while(a) {
    x = a % p;
    result[index--] = (x > 9) ? ('A' + x - 10) : ('0' + x);
    a /= p;
  }
  for (index++; index < 32; index++) {
    printf("%c", result[index]);
  }
  printf("\n");
  system("pause");
  return 0;
}
