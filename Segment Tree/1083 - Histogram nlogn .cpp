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

//For getting the size of segmentTree
int nextPowerofTwo(int n){
    int mask=1,i=1;
    while(1){
        mask=mask<<1;
        if(mask>=n) return 1<<i;
        i++;
    }
}

//Returning max of two or three integers
int max(int x,int y,int z=-inf){
    if(z==-inf) return x>y?x:y;
    return max(max(x,y),z);
}

//returning minimum of two integers
int mini(int x,int y){
    return x<y?x:y;
}

//Get index of minimum value in the input array
//Checks if ith height is less then jth height or not
int getMinValIndex(int *arr,int i,int j){
    if(i==-1) return j;
    if(j==-1) return i;
    return arr[i]<arr[j]?i:j;
}

//Creates segment tree storing the indexex of minimum values in the input array
int createSegmentTree(int *segmentTree,int *arr,int low,int high,int pos ){
    if(low > high ) return -1;
    if(low==high) return segmentTree[pos]=low;
    int mid=(low + high)/2;

    return segmentTree[pos]=getMinValIndex(arr,createSegmentTree(segmentTree,arr,low,mid,2*pos),
                           createSegmentTree(segmentTree,arr,mid +1,high,2*pos +1));
}

//Queries the minimum value index in a given range
int query(int *segmentTree,int *arr,int qlow,int qhigh,int low,int high,int pos){
    if(qlow>high or qhigh< low) return -1;
    if(low>=qlow and high <=qhigh) return segmentTree[pos];
    int mid=(low + high)/2;

    return getMinValIndex(arr,query(segmentTree,arr,qlow,qhigh,low,mid,2*pos),
                          query(segmentTree,arr,qlow,qhigh,mid+1,high,2*pos +1));
}

//Calculates a given rectangle 
int calcRectangle(int *segmentTree,int *arr,int qlow,int qhigh,int low,int high){
    if(qlow > qhigh) return -1;
    if(qlow==qhigh) return arr[qlow];

    int mid=query(segmentTree,arr,qlow,qhigh,low,high,1);
    
    /*
    Gets max between leftrectangel of the min value, not including the min
                     right rectangle of the min value, not including the min
                     the min value *(size of the rectangle)
    */
    return max(calcRectangle(segmentTree,arr,qlow,mid-1,low,high),
               calcRectangle(segmentTree,arr,mid+1,qhigh,low,high),
               (qhigh-qlow +1)*(arr[mid]));
}

int main()
{
    syncronize
    //readFile

    int test,n,len;
    cin>>test;
    int *arr,*segMentTree;

    for(int tc=1;tc<=test;tc++){
        cin>>n;
        arr=new int[n +1];
        len=nextPowerofTwo(n);
        segMentTree=new int[2*len +1];

        for(int i=1;i<=n;i++) cin>>arr[i];
        createSegmentTree(segMentTree,arr,1,n,1);

        cout<< "Case "<<tc<< ": "<<calcRectangle(segMentTree,arr,1,n,1,n)<<endl;
        free(arr),free(segMentTree);
        //cout<<calcRectangle(arr,n)<<endl;
    }


    return 0;
}

/**
1 5
1 3 2 1 2

2 7
3 3 1 4 5 1 2
5
4 4 3 2 4
*/
