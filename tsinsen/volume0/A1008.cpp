#include <stdio.h> 
#include <stdlib.h> 


int main(int argc, char const *argv[]) 
{
  int count, sum = 0, maxVal = -2147483648, minVal = 2147483647, number;
  scanf("%d", &count);
  while(count--) {
    scanf("%d", &number);
    if (number > maxVal) {
      maxVal = number;
    }
    if (number < minVal) {
      minVal = number;
    }
    sum += number;
  }
  printf("%d\n", maxVal);
  printf("%d\n", minVal);
  printf("%d\n", sum);
  system("pause");
  return 0;
}
