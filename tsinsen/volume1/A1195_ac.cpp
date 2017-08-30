#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct node
{
    int start,arrive,target;
}a[20000];
int n,m,K,ans;
int f[20000],Time[20000],g[20000],dist[20000],sum[20000];
// f: 在第i站最后一个旅客到站的时刻
// time：到第i站最小的时刻
// g：如果在第i站使用加速器，能够影响到的站点（至少是下一站）
// dist：第i站到第i+1站的时间
// sum：在第i站之前下车的旅客之和
int main()
{
    scanf("%d %d %d",&n,&m,&K);
    for (int i = 1;i < n;i ++)
        scanf("%d",&dist[i]);
    for (int i = 1;i <= m;i ++)
    {
        scanf("%d %d %d",&a[i].arrive,&a[i].start,&a[i].target);
        f[a[i].start] = max(f[a[i].start],a[i].arrive);
        sum[a[i].target] ++ ;
    }
    for (int i = 2;i <= n;i ++)
        sum[i] += sum[i - 1];

    Time[1] = 0;
    for (int i = 2;i <= n;i ++)
        Time[i] = max(Time[i - 1],f[i - 1]) + dist[i - 1];
    for (int i = 1;i <= m;i ++)
        ans += Time[a[i].target] - a[i].arrive;

    while (K)
    {
        g[n] = n;
        g[n - 1] = n;
        for (int i = n - 2;i ; i -- )
        {
            if (Time[i + 1] <= f[i + 1])
                g[i] = i + 1;
            else g[i] = g[i + 1];
        }
        int Max = 0,j;
        for (int i = 1;i <= n;i ++)
            if (sum[g[i]] - sum[i] > Max && dist[i] > 0)
                Max = sum[g[i]] - sum[i],j = i;
        if (!Max) break;
        ans -= Max;
        dist[j] --;
        K --;
        Time[1] = 0;
        for (int i = 2;i <= n;i ++)
            Time[i] = max(Time[i - 1],f[i - 1]) + dist[i - 1];
    }
    cout << ans << endl;
}