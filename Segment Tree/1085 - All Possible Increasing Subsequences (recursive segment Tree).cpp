/*
Author @Aitto_sang
CSE@Buet
*/
#include<stdio.h>
//#include<iostream>
//#include<ctime>
//#include<cmath>
//#//include<cstdlib>
#include<algorithm>
#include<map>
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
//#define syncronize ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define mod 1000000007

using namespace std;

int nextPowerofTwo(int n){
    int mask=1,i=1;
    while(1){
        mask=mask<<1;
        if(mask>=n) return 1<<i;
        i++;
    }
}

struct element{
    int data;
    int index;
};

int query(int *segmentTree,int qlow,int qhigh,int low,int high,int pos){
    if(low>=qlow and high <=qhigh) return segmentTree[pos];
    if(high<qlow or low >qhigh) return 0;
    int mid=(low + high)/2;
    return (query(segmentTree,qlow,qhigh,low,mid,2*pos) + query(segmentTree,qlow,qhigh,mid +1,high,2*pos +1))%mod;
}

int update(int *segmentTree,element *arr,int low,int high,int n,int pos,int index,int mask=0){

    if(low > index or high < index) return segmentTree[pos];
    if(low == high){
        if(mask!=0){
            int ans=0;
            for(int i=1;i<index;i++){
                if(arr[i].data!=arr[index].data) ans+=arr[i].data;
            }
            segmentTree[pos]=ans +1;
            //pf("seTting at %d -> %d\n",pos,segmentTree[pos]);
            return segmentTree[pos];
        }else{
            int x=query(segmentTree,1,index-1,1,n,1);
            //pf("settinG at %d -> %d\n",pos,x +1);
            return segmentTree[pos]= 1+ x;
        }
    }

    int mid=(low + high)/2;
    segmentTree[pos]= (update(segmentTree,arr,low,mid,n,2*pos,index,mask) + update(segmentTree,arr,mid +1,high,n,2*pos +1,index,mask))%mod;
    //pf("Setting at %d -> %d\n",pos,segmentTree[pos]);
    return segmentTree[pos];
}

bool compare(element e1, element e2){

    return e1.data<e2.data?true:false;
}

int main()
{
    //syncronize
    //readFile

    int test,n,len,tmp;
    sf("%d",&test);
    int *segmentTree;
    element *arr;

    for(int tc=1;tc<=test;tc++){
        map<int,int> mp;
        sf("%d",&n);
        len=2*nextPowerofTwo(n);
        arr=new element[n +1];
        segmentTree=new int[len +1];
        for(int i=1;i<=n;i++) sf("%d",&arr[i].data), arr[i].index=i;
        sort(arr +1,arr+n+1,compare);
//        for(int i=1;i<=n;i++){
//            pf("%d --> %d\n",arr[i].data,arr[i].index);
//        }
        for(int i=1;i<=n;i++) {
            tmp=mp[arr[i].data];
            //pf("temp: %d\n",tmp);
            //pf("step : %d\n",i);
            if(tmp==0) update(segmentTree,arr,1,n,n,1,arr[i].index);
            else update(segmentTree,arr,1,n,n,1,arr[i].index,1);
            mp[arr[i].data]++;
        }
        pf("Case %d: %d\n",tc,segmentTree[1]);
    }

    return 0;
}
/**
1 4
1 2 3 4
ans=15

3
3
1 1 2
5
1 2 1000 1000 1001
3
1 10 11
ans=5,23,7

1 7
1 2 3 3 2 3 4
ans=51


*/
