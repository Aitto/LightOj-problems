/**
Author @Aitto_sang
CSE@Buet
*/
/**
This is light OJ binary simulation problem. Which solved with lazy Segment Tree DS.
The idea is We keep updates in the lazy Tree. And Keep changes in the segment Tree.
Suppose we have two time Invert in range 1 to 10. Then the inversion will cancel each other.
*/
#include<stdio.h>
#include<iostream>
//#include<cmath>
#include<cstdlib>
//#include<algorithm>
//#include<stack>
#include<cstring>
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
// For determining next two power, to determine the size of segment Tree, according to input array.
int nextTwoPower(int n){
    int i=1,mask=1;

    while(1){
        mask=mask<<1;
        if(mask>=n) return 1<<i;
        i++;
    }
}
// Run Query in the segment Tree
int Query(int *segmentTree,int *lazyTree,int index,int low,int high,int pos){

    //Out of bound condition
    if(index<low or index >high){
        //Check if there is anything to update
        if(lazyTree[pos]!=0){
            //Propagate the update if we aren't at leaf, and make the current node zero
            if(low!=high){
                //Check children and invert them, If 1-> make zero, if 0-> make one
                if(lazyTree[2*pos]) lazyTree[2*pos]=0;
                else lazyTree[2*pos]=1;

                if(lazyTree[2*pos +1]) lazyTree[2*pos +1]=0;
                else lazyTree[2*pos +1]=1;
            }else{
                //We are at leaf node
                //As we are keeping track of changes in segment Tree,
                //we have to invert it as lazy Tree gives us a propagation
                if(segmentTree[pos]) segmentTree[pos]=0;
                else segmentTree[pos]=1;
            }

            //Making current node zero, because result been propagated
            lazyTree[pos]=0;
        }
        //A it doesn't overlap so return unexpected value
        return -1;
    }

    //If we are going in way then, propagate
    if(index>=low and index <=high){
        if(lazyTree[pos]!=0){
            if(low!=high){
                if(lazyTree[2*pos]) lazyTree[2*pos]=0;
                else lazyTree[2*pos]=1;

                if(lazyTree[2*pos +1]) lazyTree[2*pos +1]=0;
                else lazyTree[2*pos +1]=1;
            }else{
                if(segmentTree[pos]) segmentTree[pos]=0;
                else segmentTree[pos]=1;
            }
            lazyTree[pos]=0;
        }
    }

    //if we are at leaf, segment Tree been already propagated, so return the value;
    if(low==high){
        return segmentTree[pos];
    }

    //If we arenot at leaf and it overlaps then go deeper
    int mid=(low + high)/2;
    int a=Query(segmentTree,lazyTree,index,low,mid,2*pos),b=Query(segmentTree,lazyTree,index,mid +1,high,2*pos +1);

    //Check at appropriate result;
    if(a!=-1) return a;
    return b;

}

//Keep track of update in the lazy Tree
void Update(int *lazyTree,int qlow,int qhigh,int low,int high,int pos){
    //Out of bound conditions
    if(low > high) return;
    if(qlow>high or qhigh <low) return;

    //If there is a total overlap then invert the lazyTree at that position and return
    if(low>=qlow and high <=qhigh){
        if(lazyTree[pos]!=0) lazyTree[pos]=0;
        else lazyTree[pos]=1;
        return;
    }

    //if lazyTree have a propagation then send it to it's children and make itself zero
    if(lazyTree[pos]!=0){
        if(low!=high){
            if(lazyTree[2*pos]) lazyTree[2*pos]=0;
            else lazyTree[2*pos]=1;

            if(lazyTree[2*pos +1]) lazyTree[2*pos +1]=0;
            else lazyTree[2*pos +1]=1;
        }
        lazyTree[pos]=0;
    }

    int mid=(low +high)/2;
    Update(lazyTree,qlow,qhigh,low,mid,2*pos), Update(lazyTree,qlow,qhigh,mid +1,high,2*pos +1);

}

void printTree(int *arr,int len){
    for(int i=1;i<=len;i++) pf("%d ",arr[i]);
    pf("\n");
}

void print(int *arr,int low,int high,int pos){
    if(low> high) return;
    pf("(%d-%d) -> %d\n",low,high,arr[pos]);
    if(low==high) return;
    int mid=(low +high)/2;
    print(arr,low,mid,2*pos),print(arr,mid+1,high,2*pos +1);
}

int main(){
    syncronize

    int t,*segmentTree,*lazyTree,q,qlow,qhigh,qindex;
    string str;
    char ch;

    cin>>t;

    for(int i=1;i<=t;i++){
        //debug
        cin>>str>>q;
        int len=str.length(),temp;
        int n=2*nextTwoPower(len);
        segmentTree=new int[n +1];
        lazyTree=new int[n +1];

        for(int i=0;i<=n;i++) segmentTree[i]=lazyTree[i]=0;

        printf("Case %d:\n",i);
        while(q--){
            cin>>ch;

            if(ch=='I'){
                cin>>qlow>>qhigh;
                Update(lazyTree,qlow,qhigh,1,len,1);

            }
            else{
                cin>>qindex;
                temp=Query(segmentTree,lazyTree,qindex,1,len,1);
                ch=str[qindex-1];

                if(temp) if(ch=='1') pf("%c\n",'0');
                         else pf("%c\n",'1');
                else pf("%c\n",ch);
            }
        }
        //Freeing memory for reuse
        free(segmentTree), free(lazyTree);
    }

    return 0;
}

/**
Test cases:

2
0011001100
6
I 1 10
I 2 7
Q 2
Q 1
Q 7
Q 5
1011110111
6
I 1 10
I 2 7
Q 2
Q 1
Q 7
Q 5


1
0110101111010001
10
I 1 16
Q 1
I 1 3
Q 1
I 1 3
Q 1
I 1 5
Q 10
I 1 7
Q 7
*/
