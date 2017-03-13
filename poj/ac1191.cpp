#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

int MAX = 2147483647;

int MIN(int a, int b){
  if(a > b) return b;
  return a;
}

int main() {
  int N;
  int val[8][8];
  cin >> N;
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      cin >> val[i][j];
      val[i][j] *= N;
    }
  }
  int res[16][8][8][8][8] = {0};//res[n][i][j][k][l]: 分成n个，从(i,j)开始，到(k,l)结束
  //必须满足：i<=k, j<=l, k+l-i-j>=n-1
  //要求的是res[N][0][0][7][7]
  //先求sigma
  int sigma = 0;
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      sigma += val[i][j]/N;
    }
  }

  //初始值：N=1的情况
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      for(int k = i; k < 8; k++){
        for(int l = j; l < 8; l++){
          int temp = 0;
          for(int ii = i; ii <= k; ii++){
            for(int jj = j; jj <= l; jj++){
              temp += val[ii][jj];
            }
          }
          res[1][i][j][k][l] = (temp-sigma)*(temp-sigma);
        }
      }
    }
  }

  for(int n = 2; n <= N; n++){
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        for(int k = i; k < 8; k++){
          for(int l = j; l < 8; l++){
            if(k+l-i-j < n-1) continue;
            int temp = MAX;
            for(int t = i; t < k; t++){
              if(t+l-i-j>=n-2) temp = MIN(temp, res[n-1][i][j][t][l] + res[1][t+1][j][k][l]);
              if(k+l-(t+1)-j>=n-2) temp = MIN(temp, res[1][i][j][t][l] + res[n-1][t+1][j][k][l]);
            }
            for(int t = j; t < l; t++){
              if(k+t-i-j>=n-2) temp = MIN(temp, res[n-1][i][j][k][t] + res[1][i][t+1][k][l]);
              if(k+l-i-(t+1)>=n-2) temp = MIN(temp, res[1][i][j][k][t] + res[n-1][i][t+1][k][l]);
            }
            res[n][i][j][k][l] = temp;
          }
        }
      }
    }
  }
  int ans = res[N][0][0][7][7];
  double Ans = sqrt(ans * 1.0)/(N*sqrt(N*1.0));
  printf("%.3lf\n", Ans);
  return 0;
}