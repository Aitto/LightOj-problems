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

int countMaxArea(int *arr,int l,int r){
    if(l>r) return -1;
    if(l==r) return arr[l];
    int m=inf,index=-1;
    //Finds minimum in the range
    for(int i=l;i<=r;i++){
        if(arr[i]<m) {
            m=arr[i];
            index=i;
        }
    }
    
    //Finds max of left ,right and of the min value ractengle
    return max( max(countMaxArea(arr,l,index-1),
               countMaxArea(arr,index+1,r)),
               m*(r-l+1) );

}

int main()
{
    syncronize
    //readFile

    int test,n;
    cin>>test;
    int *arr;

    for(int tc=1;tc<=test;tc++){
        cin>>n;
        arr=new int[n+1];
        for(int i=1;i<=n;i++) cin>>arr[i];
        cout<< "Case "<<tc<< ": "<<countMaxArea(arr,1,n)<<endl;
        free(arr);
    }


    return 0;
}
