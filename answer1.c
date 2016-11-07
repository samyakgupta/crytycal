#include<stdio.h>
int main()
{
    long long int k,t,res;
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld",&k);
        res=192+(k-1)*250+1;
        printf("%lld\n",res);
    }
}

