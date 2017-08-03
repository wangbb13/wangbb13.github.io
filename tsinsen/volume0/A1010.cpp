#include <stdio.h> 
#include <stdlib.h> 


int main(int argc, char const *argv[]) 
{
  int a, quotient, remain;
  scanf("%d", &a);
  remain = a % 16;
  quotient = a / 16;
  printf("%c", (quotient > 9) ? ('A' + quotient - 10) : ('0' + quotient));
  printf("%c\n", (remain > 9) ? ('A' + remain - 10)   : ('0' + remain));
  system("pause");
  return 0;
}
