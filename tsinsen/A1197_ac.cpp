#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void fill(char a)
{
}
int main()
{
    char s[120]={0};
    memset(s,0,sizeof(s));
    int p1,p2,p3,i,j,k;
    scanf("%d%d%d",&p1,&p2,&p3);
    scanf("%s",s);
    for(i=0;i<strlen(s);i++)
    {
        if(s[i]=='-')
        {
            if(s[i-1]>='a' && s[i-1]<='z' && s[i+1]>='a' && s[i+1]<='z' && s[i+1]>s[i-1]
            || s[i-1]>='0' && s[i-1]<='9' && s[i+1]>='0' && s[i+1]<='9' && s[i+1]>s[i-1])
            {
                if(p1==3)
                {
                    for(j=1;j<=p2*(s[i+1]-s[i-1]-1);j++)
                    {
                        printf("*");
                    }
                }
                else
                {
                    if(s[i-1]>='0' && s[i-1]<='9' && s[i+1]>='0' && s[i+1]<='9')
                    {
                        if(p3==1)
                        {
                            for(j=s[i-1]+1;j<=s[i+1]-1;j++)
                            {
                                for(k=1;k<=p2;k++)
                                {
                                    printf("%c",j);
                                }
                            }
                        }
                        else
                        {
                            for(j=s[i+1]-1;j>=s[i-1]+1;j--)
                            {
                                for(k=1;k<=p2;k++)
                                {
                                    printf("%c",j);
                                }
                            }
                        }
                    }
                    else
                    {
                        if(p3==1)
                        {
                            for(j=s[i-1]+1;j<=s[i+1]-1;j++)
                            {
                                for(k=1;k<=p2;k++)
                                {
                                    printf("%c",p1==1?j:j-32);
                                }
                            }
                        }
                        else
                        {
                            for(j=s[i+1]-1;j>=s[i-1]+1;j--)
                            {
                                for(k=1;k<=p2;k++)
                                {
                                    printf("%c",p1==1?j:j-32);
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                printf("%c",s[i]);
            }
        }
        else
        {
            printf("%c",s[i]);
        }
    }
    return 0;
}