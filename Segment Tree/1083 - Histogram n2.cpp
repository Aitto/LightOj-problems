/**
n^2 algo for histogram problem..... has tle
*/
/**
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
#define linf 1e15
#define NULL_VALUE -999999
#define maxNEG -99999999.0
#define debug cout<<"Hello here!"<<endl;
#define readFile freopen("in.txt","r",stdin);
#define syncronize ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

using namespace std;

int nextPowerOfTwo(int n){
    int mask=1,ans=1,i=1;

    while(1){
        mask=mask<<1;
        if(mask>=n) return  1<<i;
        i++;
    }
}

void createSegmntTree(int *segmentTree,int *arr,int low,int high,int pos){
   if(high==low){
        segmentTree[pos]=arr[low];
        return;
    }

    int mid=(low + high)/2;

    createSegmntTree(segmentTree,arr,low,mid,2*pos), createSegmntTree(segmentTree,arr,mid+1,high,2*pos +1);
    segmentTree[pos]=min(segmentTree[2*pos],segmentTree[2*pos +1]);
}

int query(int *segmentTree,int qlow,int qhigh,int low,int high,int pos){
    if(qlow>high or qhigh <low) return inf;

    if(low >=qlow and high<=qhigh) return segmentTree[pos];

    int mid=(low +high)/2;

    int a=query(segmentTree,qlow,qhigh,low,mid,2*pos), b=query(segmentTree,qlow,qhigh,mid +1,high,2*pos +1);
    return a<b?a:b;
}

int main()
{
    syncronize
    //readFile

    int test,n,len;
    cin>>test;
    int *arr,*segmentTree;

    for(int tc=1;tc<=test;tc++){
        cin>>n;
        len=nextPowerOfTwo(n) *2;
        arr=new int[n +1];
        segmentTree=new int[len +1];

        for(int i=1;i<=n;i++) cin>>arr[i];

        createSegmntTree(segmentTree,arr,1,n,1);
        //for(int i=1;i<=len;i++) cout<< segmentTree[i] << " ";
        //cout<<endl;
        int ans=0,temp;
        for(int i=1;i<=n;i++){
            for(int j=i;j<=n;j++) {
                temp=query(segmentTree,i,j,1,n,1);
                //cout<< "("<<i<<","<<j<<")->"<<temp<<endl;
                if(ans < temp*(j-i+1)) ans=temp*(j-i+1);
            }
        }

        cout<< "Case "<<tc<< ": "<<ans<<endl;

    }


    return 0;
}
