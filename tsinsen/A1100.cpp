#include <cstdio>
#include <cstdlib>

int main(int argc, char const *argv[])
{
  int a, b, c;
  scanf("%d %d", &a, &b);
  printf("%d\n", a);
  printf("* %d\n", b);
  printf("----\n");
  if (b > 10) {
    c = b % 10;
    printf("%4d\n", (a * c));
    c = b / 10;
    printf("%3d\n", (a * c));
    printf("----\n");
    printf("%4d\n", (a * b));
  } else {
    printf("%3d\n", (a * b));
  }
  return 0;
}