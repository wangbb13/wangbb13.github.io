#include <stdio.h> 
#include <stdlib.h> 


int main(int argc, char const *argv[]) 
{
  int threshold, i, j, k, number;
  printf("THRESHOLD: ");
  scanf("%d", &threshold);
  if (threshold > 54 || threshold < 2) {
    system("pause");
    return 0;
  }
  if (threshold <= 45) {
    for (i = 1; i < 10; i++) {
      for (j = 0; j < 10; j++) {
        for (k = 0; k < 10; k++) {
          if ((i * 2 + j * 2 + k) == threshold) {
            number = i * 10001 + j * 1010 + k * 100;
            printf("%d\n", number);
          }
        }
      }
    }
  }
  for (i = 1; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      for (k = 0; k < 10; k++) {
        if ((2*(i+j+k)) == threshold) {
          number = i * 100001 + j * 10010 + k * 1100;
          printf("%d\n", number);
        }
      }
    }
  }
  system("pause");
  return 0;
}
