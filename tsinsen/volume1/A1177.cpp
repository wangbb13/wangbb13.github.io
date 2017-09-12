/*
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

int w[10][10] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 6, 6, 6, 6, 6, 6, 6, 6, 6},
  {0, 6, 7, 7, 7, 7, 7, 7, 7, 6},
  {0, 6, 7, 8, 8, 8, 8, 8, 7, 6},
  {0, 6, 7, 8, 9, 9, 9, 8, 7, 6},
  {0, 6, 7, 8, 9, 10, 9, 8, 7, 6},
  {0, 6, 7, 8, 9, 9, 9, 8, 7, 6},
  {0, 6, 7, 8, 8, 8, 8, 8, 7, 6},
  {0, 6, 7, 7, 7, 7, 7, 7, 7, 6},
  {0, 6, 6, 6, 6, 6, 6, 6, 6, 6}
};

int idx[10][10] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
  {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
  {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
  {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
  {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
  {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
  {0, 7, 7, 7, 8, 8, 8, 9, 9, 9},
  {0, 7, 7, 7, 8, 8, 8, 9, 9, 9},
  {0, 7, 7, 7, 8, 8, 8, 9, 9, 9},
};

int ipt[10][10] = {0};
int row[10][10] = {0}, col[10][10], sq[10][10] = {0};
int ans = -1;

void deal(int x, int y) {
  if (x == 0 && y == 0) {
    int val = 0;
    for (int i = 1; i < 10; i++) {
      for (int j = 1; j < 10; j++) {
        val += (w[i][j] * ipt[i][j]);
      }
    }
    ans = max(ans, val);
    return;
  }
  if (ipt[x][y] != 0) {
    if (x == 9 && y == 9) {
      deal(0, 0);
    } else if (y == 9) {
      deal(x+1, 1);
    } else {
      deal(x, y+1);
    }
  } else {
    for (int i = 1; i < 10; i++) {
      if (row[x][i] == 0 && col[y][i] == 0 && sq[idx[x][y]][i] == 0) {
        ipt[x][y] = i;
        row[x][i] = 1;
        col[y][i] = 1;
        sq[idx[x][y]][i] = 1;
        if (x == 9 && y == 9) {
          deal(0, 0);
        } else if (y == 9) {
          deal(x+1, 1);
        } else {
          deal(x, y+1);
        }
        ipt[x][y] = 0;
        row[x][i] = 0;
        col[y][i] = 0;
        sq[idx[x][y]][i] = 0;
      }
    }
  }
}

int main() {
  int v;
  for (int i = 1; i < 10; i++) {
    for (int j = 1; j < 10; j++) {
      scanf("%d", &v);
      ipt[i][j] = v;
      row[i][v] = 1;
      col[j][v] = 1;
      sq[idx[i][j]][v] = 1;
    }
  }
  deal(1, 1);
  printf("%d\n", ans);
  return 0;
}
*/

// 不超时版本
#include <iostream> 
#include <cstdio> 
#include <cstdlib> 
#include <cstring> 

using namespace std; 
int s[9][9]; 
int w[9][9] = { 
        {6, 6, 6, 6, 6, 6, 6, 6, 6,}, 
        {6, 7, 7, 7, 7, 7, 7, 7, 6,}, 
        {6, 7, 8, 8, 8, 8, 8, 7, 6,}, 
        {6, 7, 8, 9, 9, 9, 8, 7, 6,}, 
        {6, 7, 8, 9, 10, 9, 8, 7, 6,}, 
        {6, 7, 8, 9, 9, 9, 8, 7, 6,}, 
        {6, 7, 8, 8, 8, 8, 8, 7, 6,}, 
        {6, 7, 7, 7, 7, 7, 7, 7, 6,}, 
        {6, 6, 6, 6, 6, 6, 6, 6, 6,}}; 
int ans = -1; 
int tb[9][9] = { 
    {0, 0, 0, 1, 1, 1, 2, 2, 2, }, 
    {0, 0, 0, 1, 1, 1, 2, 2, 2, }, 
    {0, 0, 0, 1, 1, 1, 2, 2, 2, }, 
    {3, 3, 3, 4, 4, 4, 5, 5, 5, }, 
    {3, 3, 3, 4, 4, 4, 5, 5, 5, }, 
    {3, 3, 3, 4, 4, 4, 5, 5, 5, }, 
    {6, 6, 6, 7, 7, 7, 8, 8, 8, }, 
    {6, 6, 6, 7, 7, 7, 8, 8, 8, }, 
    {6, 6, 6, 7, 7, 7, 8, 8, 8, }, 
}; 

int r[9][10], c[9][10], b[9][10]; 

void dfs(int k, int sum) 
{ 
    int x=k/9, y=k%9; 
    if(k >= 0 && s[x][y] != 0) 
       dfs(k-1, sum + s[x][y]*w[x][y]); 
    else 
      if(k == -1) 
         if(sum > ans) ans = sum; 
            else; 
      else 
         for(int i = 1; i <= 9; i++) 
            if(!r[x][i] && !c[y][i] && !b[tb[x][y]][i]) 
            { 
                r[x][i] = c[y][i] = b[tb[x][y]][i] = 1; 
                dfs(k-1, sum+i*w[x][y]); 
                r[x][i] = c[y][i] = b[tb[x][y]][i] = 0; 
            } 
} 

int main() 
{ 
    for(int i=0; i<9; i++) 
       for(int j=0; j<9; j++) 
       { 
           int a; 
           scanf("%d", &a); 
           s[i][j]=a; 
           if(a) r[i][a] = c[j][a] = b[tb[i][j]][a] = 1; 
       } 
    dfs(80, 0); 
    printf("%d\n", ans); 
    return 0; 
}
