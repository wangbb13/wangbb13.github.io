#include <stdio.h> 
#include <stdlib.h> 

/*
 * single wooden birdge question
 * input:  L N a, [, b] (len(..) = N)
 * output: minTime, maxTime
 */

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

int main(int argc, char const *argv[]) 
{
  int l, n, p, minTime = 0, maxTime = 0;
  scanf("%d", &l);
  scanf("%d", &n);
  while(n--) 
  {
    scanf("%d", &p);
    minTime = max(minTime, min(p, l + 1 - p));
    maxTime = max(maxTime, max(p, l + 1 - p));
  }
  printf("%d %d\n", minTime, maxTime);
  system("pause");
  return 0;
}
