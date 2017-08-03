#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

int main(int argc, char const *argv[]) 
{
  char input[1001];
  char array[1001];
  int subLen = 0, arrayLen = 0;
  scanf("%s", input);
  scanf("%d", &subLen);
  arrayLen = strlen(input) - subLen + 1;
  for (int i = 0; i < arrayLen; i++) {
    array[i] = i;
  }
  for (int i = 0; i < arrayLen; i++) {
    for (int j = arrayLen - 1; j > i; j--) {
      if (strncmp((input + array[j]), (input + array[j-1]), subLen) < 0) {
        int temp = array[j];
        array[j] = array[j-1];
        array[j-1] = temp;
      }
    }
  }
  for (int i = 0; i < arrayLen; i++) {
    for (int j = array[i]; ; j++) {
      if (j - array[i] + 1 > subLen) {
        break;
      }
      printf("%c", input[j]);
    }
    printf(" ");
  }
  printf("\n");
  system("pause");
  return 0;
}
