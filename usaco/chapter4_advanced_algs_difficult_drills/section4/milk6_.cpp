/*
ID: wangbb21
LANG: C++11
TASK: milk6
*/
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long ll;
const int inf=99999999;
struct node
{
    int x,y,c,next,other,ds;
}a[2100],d[2100];int len,last[2100];
void ins(int x,int y,int c)
{
    len++;int k1=len;
    a[len].x=x;a[len].y=y;a[len].c=c;
    a[len].next=last[x];last[x]=len;
    len++;int k2=len;
    a[len].x=y;a[len].y=x;a[len].c=0;
    a[len].next=last[y];last[y]=len;
    a[k1].other=k2;
    a[k2].other=k1;
}
int list[2100],head,tail,h[2100];
int st,ed,b[2100],lenb;
bool bfs()
{
    memset(h,0,sizeof(h));h[st]=1;
    list[1]=st;head=1;tail=2;
    while(head<tail)
    {
        int x=list[head];
        for(int k=last[x];k;k=a[k].next)
        {
            int y=a[k].y;
            if(h[y]==0&&a[k].c>0)
            {
                h[y]=h[x]+1;
                list[tail]=y;
                tail++;
            }
        }
        head++;
    }
    if(h[ed]==0)return false;
    else return true;
}
int findflow(int x,int f)
{
    if(x==ed)return f;
    int s=0;
    for(int k=last[x];k;k=a[k].next)
    {
        int y=a[k].y;
        if(h[y]==h[x]+1&&a[k].c>0&&s<f)
        {
            int t=findflow(y,min(a[k].c,f-s));
            s+=t;a[k].c-=t;a[a[k].other].c+=t;
        }
    }
    if(s==0)h[x]=0;
    return s;
}
int cmp(const void *xx,const void *yy)
{
    node n1=*(node *)xx;
    node n2=*(node *)yy;
    if(n1.c<n2.c)return 1;
    else return -1;
}
bool bk[21000];
int main()
{
    freopen("milk6.in","r",stdin);
    freopen("milk6.out","w",stdout);
    int n,m;scanf("%d%d",&n,&m);
    len=0;memset(last,0,sizeof(last));
    for(int i=1;i<=m;i++)
    {
        int x,y,c;scanf("%d%d%d",&x,&y,&c);
        ins(x,y,c);d[i].x=x;d[i].y=y;d[i].c=c;d[i].ds=i;
    }
    st=1;ed=n;
    ll ans=0;
    while(bfs()==true)ans+=findflow(st,inf);
    printf("%lld ",ans);
    qsort(d+1,m,sizeof(node),cmp);
    memset(bk,false,sizeof(bk));int kk=len;
    for(int i=1;i<=m;i++)
    {
        if(d[i].c<=ans)
        {
            memset(last,0,sizeof(last));
            len=0;
            for(int j=1;j<=m;j++)
            {
                if(bk[d[j].ds]==false&&i!=j)ins(d[j].x,d[j].y,d[j].c);
            }
            ll sum=0;
            while(bfs()==true)sum+=findflow(st,inf);
            if(sum+d[i].c==ans)
            {
                ans-=d[i].c;
                bk[d[i].ds]=true;
                b[++lenb]=d[i].ds;
            }
        }
    }
    printf("%d\n",lenb);
    if(lenb!=0)
    {
        sort(b+1,b+lenb+1);
        for(int i=1;i<=lenb;i++)printf("%d\n",b[i]);
    }
    return 0;
}
