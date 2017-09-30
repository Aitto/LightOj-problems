#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cmath>


#define sf scanf
#define pf printf
#define Minus_Infinite -99999999
#define Minus_Long_Infinite -999999999999999

using namespace std;

/*double intbaselog(double base,double num){
    return (double) log(num)/log(base);
}

long long int digits(int num,int base){\
    double sum=0.0;
    for(int i=1;i<=num;i++){
        sum+=intbaselog(base,i);
    }

    return (long long int) floor(sum) +1;
}*/


int calc(int num,int base){

}

int main(){

    int test,num;
    double base;

    int ans=0;
    double dp[1000005];
    dp[0]=0.0;

    for(int i=1;i<=1000001;i++){
        dp[i]=dp[i-1] +log(i);
    }

    sf("%d",&test);

    for(int i=1;i<=test;i++){
        sf("%d %lf",&num,&base);

        if(num==0 or num==1){
            pf("Case %d: %d\n",i,1);
            continue;
        }else{
            ans=ceil(dp[num]/log(base));
            pf("Case %d: %d\n",i,ans);
        }
    }

    return 0;
}

