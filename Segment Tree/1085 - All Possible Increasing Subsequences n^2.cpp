/*
Author @Aitto_sang
CSE@Buet
*/
#include<stdio.h>
#include<iostream>
//#include<ctime>
//#include<cmath>
//#//include<cstdlib>
#include<algorithm>
//#include<stack>
//#include<cstring>
//#include<bits/stdc++.h>

#define lli long long int
#define pf printf
#define sf scanf
#define pi 3.141592653589793116
#define inf 1e9
#define linf 1e18
#define NULL_VALUE -999999
#define maxNEG -inf
#define debug cout<<"Hello here!"<<endl;
#define readFile freopen("in.txt","r",stdin);
#define syncronize ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

using namespace std;

int countAll(int *arr,int n){
    int ans=0,*temp=new int[n +1];
    for(int i=0;i<n;i++) temp[i]=1;

    for(int i=1;i<n;i++)
        for(int j=0;j<i;j++)
        if(arr[i]>arr[j]) temp[i]+=temp[j];

    for(int i=0;i<n;i++) ans+=temp[i];

    return ans;
}

int main()
{
    syncronize
    //readFile
    int test;
    cin>>test;
    int *arr,n;

    for(int tc=1;tc<=test;tc++){
        cin>>n;
        arr=new int[n +1];
        for(int i=0;i<n;i++) cin>>arr[i];
        cout<< "Case "<<tc<< ": "<<countAll(arr,n)<<endl;
        free(arr);
    }

    return 0;
}
