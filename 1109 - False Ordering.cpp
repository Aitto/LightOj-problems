#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<algorithm>


#define sf scanf
#define pf printf


using namespace std;

//structing a structure for storing data
struct num{
    int data;
    int divisors;
};

//Calculating the number of divisors
int calc(int n){
    int c=sqrt(n),count=0;

    for(int i=1;i<=c;i++){
        if(n%i==0) count++;
    }

    if(c*c==n) count= count*2 -1;
    else count = count*2;
    return count;

}

//Writing our own compare function
bool compare(num a,num b){
    return (a.divisors < b.divisors) or ((a.divisors==b.divisors) and (a.data>b.data ));
}


int main()
{

    int test,n;

    num dp[1001];

    for(int i=1;i<=1000;i++){
        dp[i].data=i;
        dp[i].divisors=calc(i);
    }

    //comparing using our own compare function
    sort(dp,dp+1001,compare);

    sf("%d",&test);
    for(int i=1;i<=test;i++){
        sf("%d",&n);
        pf("Case %d: %d\n",i,dp[n].data);
    }

    return 0;
}
