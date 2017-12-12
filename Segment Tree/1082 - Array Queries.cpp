/*/**
Author @Aitto_sang
CSE@Buet
*/
#include<stdio.h>
#include<iostream>
#include<algorithm>


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
    int mask=1,i=1;

    while(1){
        mask=mask<<1;
        if(mask>=n) return 1<<i;
        i++;
    }
}

void makeTree(int *segmentTree,int *arr,int low,int high,int pos){
    if(low> high) return;
    if(low==high){
        segmentTree[pos]=arr[low];
        return;
    }

    int mid=(low +high)/2;

    makeTree(segmentTree,arr,low,mid,2*pos), makeTree(segmentTree,arr,mid +1,high,2*pos +1);
    segmentTree[pos]=min(segmentTree[2*pos],segmentTree[2*pos +1]);
}

int query(int *segmentTree,int qlow,int qhigh,int low,int high,int pos){
    if(low > high) return inf;
    if(qlow>high or qhigh < low) return inf;
    if(low>=qlow and high <=qhigh) return segmentTree[pos];

    int mid=(low + high)/2;

    int a=query(segmentTree,qlow,qhigh,low,mid,2*pos), b=query(segmentTree,qlow,qhigh,mid +1,high,2*pos +1);
    return a<b?a:b;
}

int main()
{
    syncronize
    //readFile

    int test,n,q,qlow,qhigh,*arr,*segmentTree,len;
    cin>>test;

    for(int tc=1;tc<=test;tc++){
        cin>>n>>q;
        arr=new int[n +1];
        len=2*nextPowerOfTwo(n);
        segmentTree=new int[len +1];

        for(int i=1;i<=n;i++) cin>>arr[i];

        makeTree(segmentTree,arr,1,n,1);

        pf("Case %d:\n",tc);
        for(int i=0;i<q;i++){
            cin>>qlow>>qhigh;
            pf("%d\n",query(segmentTree,qlow,qhigh,1,n,1));
        }
        free(segmentTree);
        free(arr);
    }

    return 0;
}
