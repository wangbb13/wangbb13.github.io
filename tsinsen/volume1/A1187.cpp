#include <iostream>
#include <string.h>
using namespace std;

const int INF = 1000005;
char  a[15], b[INF];

int main()
{
    int i,j,k=0,n1,n2,p;
    bool flag;
    cin.getline(a,10);     strlwr(a);  n1=  strlen(a);
    cin.getline(b,1000000);strlwr(b);  n2=  strlen(b);
    for (i=0 ; i< n2 ;i++){
        if ((b[i-1]!=' ' && i!=0)|| (b[i+n1]!=' ' && i+n1!=n2)) continue;
        flag=1;
        for (j=0;j < n1;j++) 
            if (b[i+j]!=a[j]) {flag=0;break;}
        if (flag) {
           k++;
           if (k==1) p=i;           
        }
    }
    if (k>0) cout<<k<<" "<<p<<endl; else cout<<"-1"<<endl;
    return 0;
}