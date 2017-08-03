#include <cstdio> 
#include <cstdlib> 
#include <cstring> 
using namespace std; 
int n, w[30], l[30][30]; 
int f[30], an[30], ans; 
int re[30]; 
bool j[30]; 
void inp() 
{ 
    scanf("%d",&n); 
    for(int i = 1; i <= n; ++i) scanf("%d",&w[i]); 
    for(int i = 1; i < n; ++i) 
        for(int j = i + 1; j <= n; ++j) 
        { 
            scanf("%d",&l[i][j]); 
            l[j][i] = l[i][j]; 
        } 
} 
void se(int last,int tot,int p) 
{ 
    bool juge = true; 
    for(int i = 1; i <= n; ++i) 
        if(j[i] && l[last][i])  
        { 
            juge = j[i] = false; re[p] = i; 
            se(i,tot + w[i],p+1); 
            j[i] = true; re[p] = 0; 
        } 
    if(juge) 
        if(tot > ans) 
        { 
            ans = tot; 
            for(int i = 1; i <= p; ++i) an[i] = re[i]; 
        } 
}   
int main() 
{ 
    inp(); 
    memset(j, true, sizeof(j)); 
    for(int i = 1; i <= n; ++i)  
    { 
        j[i] = false; re[1] = i; 
        se(i,w[i],2); 
        j[i] = true; re[1] = 0; 
    } 
    printf("%d",an[1]); 
    int f = 1; 
    while(an[++f] != 0) printf("-%d",an[f]); 
    printf("\nMAX=%d",ans); 
    //system("pause"); 
    return 0; 
} 