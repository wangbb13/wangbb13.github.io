#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  int i, j, k, number;
  for (i = 1; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      for (k = 0; k < 10; k++) {
        number = i * 100 + j * 10 + k;
        if (((int)pow(i, 3) + (int)pow(j, 3) + (int)pow(k, 3)) == number) {
          printf("%d\n", number);
        }
      }
    }
  }
  system("pause");
  return 0;
}