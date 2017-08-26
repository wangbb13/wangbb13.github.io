// 问题分类：单调队列
// version1
/*
#include <iostream>
#include <deque>
#include <vector>
using namespace std;

vector<int> ipt(1000002, 0);
vector<int> resi(1000002, 0);
vector<int> resx(1000002, 0);
int N, K;

int main() {
  int i, j, k = 0;
  deque<int> mi, mx;
  cin >> N >> K;
  for (i = 0; i < N; i++) {
    cin >> ipt[i];
  }
  for (i = 0; i < N; i++) {
    while (!mi.empty() && ipt[mi.back()] > ipt[i]) {
      mi.pop_back();
    }
    mi.push_back(i);
    while (!mx.empty() && ipt[mx.back()] < ipt[i]) {
      mx.pop_back();
    }
    mx.push_back(i);
    if (i >= K-1) {
      resi[k] = ipt[mi.front()];
      if (i - mi.front() >= K - 1) {
        mi.pop_front();
      }
      resx[k] = ipt[mx.front()];
      if (i - mx.front() >= K - 1){
        mx.pop_front();
      }
      k++;
    }
  }
  for (i = 0; i < k; i++) {
    cout << resi[i] << " ";
  }
  cout << endl;
  for (i = 0; i < k; i++) {
    cout << resx[i] << " ";
  }
  cout << endl;
  return 0;
}
*/
// version2
//poj-2823--单调队列  
#include<iostream>  
#include<cstdio>  
using namespace std;  

const int MAX = 1000001;  
//两个单调队列  
int dq1[MAX];    //一个存单调递增  
int dq2[MAX];    //一个存单调递减  
int a[MAX];  
  
inline bool scan_d(int &num)  //  这个就是 加速的 关键了     
{  
    char in;bool IsN=false;  
    in=getchar();  
    if(in==EOF)  
        return false;  
    while(in!='-'&&(in<'0'||in>'9')) in=getchar();  
    if(in=='-')   { IsN=true;num=0;}  
    else num=in-'0';  
    while(in=getchar(),in>='0'&&in<='9')  
    {  
        num*=10,num+=in-'0';  
    }  
    if(IsN)  
        num=-num;  
    return true;  
}  
  
int main(void)  
{  
    int i,n,k,front1,front2,tail1,tail2,start,ans;  
  
    while(scanf("%d %d",&n,&k)!=EOF)  
    {  
        for(i = 0 ; i < n ; ++i)  
            scan_d(a[i]);  
        front1 = 0, tail1 = -1;  
        front2 = 0, tail2 = -1;  
        ans = start = 0;  
        for(i = 0 ; i < k ; ++i)  
        {  
            while(front1 <= tail1 && a[ dq1[tail1] ] <= a[i])   //当前元素大于单调递增队列的队尾元素的时候，队尾的元素依次弹出队列，直到队尾元素大于当前当前元素的时候，将当前元素插入队尾  
                --tail1;  
            dq1[ ++tail1 ] = i;    //只需要记录下标即可  
  
            while(front2 <= tail2 && a[ dq2[tail2] ] >= a[i])   //当前元素小于单调递减队列的队尾元素的时候，队尾的元素依次弹出队列，直到队尾元素小于当前当前元素的时候，将当前元素插入队尾  
                --tail2;  
            dq2[ ++tail2 ] = i;    //只需要记录下标即可  
        }  
        printf("%d ",a[ dq2[ front2 ] ]);  
        for( ; i < n ; ++i)  
        {  
            while(front2 <= tail2 && a[ dq2[tail2] ] >= a[i])  
                --tail2;  
            dq2[ ++tail2 ] = i;   
            while(dq2[ front2 ] <= i - k)  
                ++front2;  
            if(i != n-1)  
                printf("%d ",a[ dq2[ front2 ] ]);  
        }  
        printf("%d\n",a[ dq2[ front2 ] ]);  
          
        //输出最大值  
        printf("%d ",a[ dq1[ front1 ] ]);  
        for(i=k ; i < n ; ++i)  
        {  
            while(front1 <= tail1 && a[ dq1[tail1] ] <= a[i])  
                --tail1;  
            dq1[ ++tail1 ] = i;   
            while(dq1[ front1 ] <= i - k)  
                ++front1;  
            if(i != n-1)  
                printf("%d ",a[ dq1[ front1 ] ]);  
        }  
        printf("%d\n",a[ dq1[ front1 ] ]);  
    }  
    return 0;  
}