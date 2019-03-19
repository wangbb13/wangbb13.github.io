#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 101;
const int MOD = 9999973;
int n,m;
ll dp[MAXN][MAXN][MAXN];
inline int C( int num ) { // 相当于C(num,2)
    return num*(num-1)/2;
}
int main() {
    scanf( "%d%d", &n, &m );
    dp[0][0][0] = 1;
    for( int i = 0; i < n; ++i ) // 放第i+1行
    for( int j = 0; j <= m; ++j ) // 有1个棋子的列数
    for( int k = 0; j+k <= m; ++k ) if( dp[i][j][k] ) { // 有2个棋子的列数
        dp[i+1][j][k] = ( dp[i+1][j][k] + dp[i][j][k] ) % MOD; // 不放
        if( m-j-k >= 1 ) dp[i+1][j+1][k] = ( dp[i+1][j+1][k] + dp[i][j][k]*(m-j-k) ) % MOD; // 放一个，在没有棋子的那一列
        if( j >= 1 ) dp[i+1][j-1][k+1] = ( dp[i+1][j-1][k+1] + dp[i][j][k]*j ) % MOD; // 放一个，在有一个棋子的那一列
        if( m-j-k >= 2 ) dp[i+1][j+2][k] = ( dp[i+1][j+2][k] + dp[i][j][k]*C(m-j-k) ) % MOD; // 放两个，都在没有棋子的两列
        if( m-j-k >= 1 && j >= 1 ) dp[i+1][j][k+1] = ( dp[i+1][j][k+1] + dp[i][j][k]*(m-j-k)*j ) % MOD; // 放两个，一个在没有棋子的列，一个在有一个棋子的列
        if( j >= 2 ) dp[i+1][j-2][k+2] = ( dp[i+1][j-2][k+2] + dp[i][j][k]*C(j) ) % MOD; // 两个，在一个棋子的列
    }
    ll ans = 0;
    for( int i = 0; i <= m; ++i ) // 有1个棋子的列
    for( int j = 0; i+j <= m; ++j ) { // 2个棋子的列
        ans = ( ans + dp[n][i][j] ) % MOD;
    }
    printf( "%lld\n", ans );
    return 0;
}