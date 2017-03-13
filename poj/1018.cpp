#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

struct node
{
  int bandwidth, price, kind;
};

node divice[10001];
int num[101];

bool cmp( node a, node b )
{
  if ( a.bandwidth < b.bandwidth )
    return true;
  else if ( a.bandwidth == b.bandwidth )
  {
    if ( a.price < b.price )
      return true;
    else if ( a.price == b.price )
    {
      if ( a.kind < b.kind )
        return true;
      else
        return false;
    }
    else
      return false;
  }
  else
    return false;
}

int main()
{
  int testNumber;
  scanf("%d", &testNumber);
  for ( int testCount = 1 ; testCount<= testNumber ; testCount ++ )
  {
    int number;
    scanf("%d", &number);
    int count = 0;
    int maxWidth[101];
    for ( int i = 0 ; i < number ; i ++ )
      maxWidth[i] = 0;
    for ( int i = 0 ; i < number ; i ++ )
    {
      scanf("%d", &num[i]);
      for ( int j = 0 ; j < num[i] ; j ++ )
      {
        scanf("%d%d", &(divice[count].bandwidth), &(divice[count].price));
        divice[count].kind = i;
        if ( divice[count].bandwidth > maxWidth[i] )
          maxWidth[i] = divice[count].bandwidth;
        count ++;
      }
    }

    sort( divice, divice+count, cmp );

    int minMaxWidth = 9999999;
    for ( int i = 0 ; i < number ; i ++ )
    {
      if ( maxWidth[i] < minMaxWidth )
        minMaxWidth = maxWidth[i];
    }

    double maxResult = 0;
    for ( int i = 0 ; i < count - number + 1  ; i ++ )
    {
      int minPrice[101];
      for ( int j = 0 ; j < number ; j ++ )
      {
        minPrice[j] = 9999999;
      }
      int tempBandwidth = divice[i].bandwidth, tempPrice = divice[i].price, tempKind = divice[i].kind;
      for ( int j = i + 1 ; j < count ; j ++ )
      {
        if ( divice[j].kind != tempKind && divice[j].price < minPrice[divice[j].kind] )
          minPrice[divice[j].kind] = divice[j].price;
      }
      for ( int j = 0 ; j < number ; j ++ )
      {
        if ( j != tempKind )
          tempPrice += minPrice[j];
      }
      if ( maxResult < (double)tempBandwidth/tempPrice )
        maxResult = (double)tempBandwidth/tempPrice;
    }
    printf("%.3f\n", maxResult);
  }
}