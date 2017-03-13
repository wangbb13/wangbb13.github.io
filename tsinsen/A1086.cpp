#include <stdio.h> 
#include <stdlib.h> 

/*
 * Huffman tree
 */

void Exchange(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void MinHeapify(int* array, int index) {
  int l = index * 2;
  int r = index * 2 + 1;
  int size = array[0];
  int minIndex = index;
  if (l <= size && array[index] > array[l]) {
    minIndex = l;
  }
  if (r <= size && array[minIndex] > array[r]) {
    minIndex = r;
  }
  if (minIndex != index) {
    Exchange((array + minIndex), (array + index));
    MinHeapify(array, minIndex);
  }
}

void BuildMinHeap(int* array) {
  for (int i = array[0] / 2; i > 0; i--) {
    MinHeapify(array, i);
  }
}

int main(int argc, char const *argv[]) 
{
  int array[101];
  int n, cost = 0, oneCost = 0, exIndex = 0;
  scanf("%d", &n);
  array[0] = n;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &array[i]);
  }
  if (n < 2) {
    printf("0\n");
    system("pause");
    return 0;
  }
  BuildMinHeap(array);
  while(array[0] > 2) {
    if (array[2] < array[3]) {
      oneCost = array[1] + array[2];
      exIndex = 2;
    } else {
      oneCost = array[1] + array[3];
      exIndex = 3;
    }
    cost += oneCost;
    Exchange((array + array[0]), (array + exIndex));
    array[0]--;
    MinHeapify(array, exIndex);
    array[1] = oneCost;
    MinHeapify(array, 1);
  }
  cost += array[1] + array[2];
  printf("%d\n", cost);
  system("pause");
  return 0;
}
