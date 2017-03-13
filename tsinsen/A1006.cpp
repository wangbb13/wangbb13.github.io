#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  int i, j, number;
  for (i = 1; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      number = i * 1001 + j * 110;
      printf("%d\n", number);
    }
  }
  system("pause");
  return 0;
}