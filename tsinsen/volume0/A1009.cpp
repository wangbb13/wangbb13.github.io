#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

void exchange(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main(int argc, char const *argv[]) 
{
  int squareSum = 0, maxVal = -1001, minusMaxVal = -1001, minVal = 1001, minusMinVal = 1001;
  int count, number, temp, remember;
  scanf("%d", &count);
  while (count--) {
    scanf("%d", &number);
    remember = number;
    if (number > maxVal) {
      exchange(&number, &maxVal);
    }
    if (number > minusMaxVal) {
      exchange(&number, &minusMaxVal);
    }
    number = remember;
    if (number < minVal) {
      exchange(&number, &minVal);
    }
    if (number < minusMinVal) {
      exchange(&number, &minusMinVal);
    }
    number = remember;
    squareSum += (int)pow(number, 2);
  }
  if (minusMaxVal == -1001) {
    minusMaxVal = remember;
  }
  if (minusMinVal == 1001) {
    minusMinVal = remember;
  }
  printf("%d\n", minusMaxVal);
  printf("%d\n", minusMinVal);
  printf("%d\n", squareSum);
  system("pause");
  return 0;
}
