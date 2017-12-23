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
//#include<map>
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
#define mod 1000000007

using namespace std;

//Finding the next two's power greater than or equal to n
int nextPowerOfTwo(int n){
    int i=1,mask=1;
    while(1){
        mask=mask<<1;
        if(mask>=n) return 1<<i;
        i++;
    }
}

//{arr[i],i} touple for storing original position even if data is sorted
struct element{
    int data;
    int index;
};

//segment Tree
struct segmentTree{
    int n,len;
    int *st;    //segment Tree indexed at 1 and input array indexed at 0

    //initializing the segmentTree
    segmentTree(int s){
        n=s;
        len=2*nextPowerOfTwo(n);
        st=new int[len +1];
        for(int i=0;i<len;i++) st[i]=0;
    }

    //Destructor code... Free all pointers to optimize memory
    ~segmentTree(){
        free(st);
    }

    //building the tree
    void build(){
        /** starting from n-1 to 1
            bellow is similar to st[i]= st[2*i] + st[2*i +1];
        */
        for(int i=n-1;i>0;i--) st[i]= st[i<<1] + st[i<<1|1];
    }

    //updating value at a certain position
    void update(int pos,int value){
        /** Putting value at pos+n position in the segment Tree.
            With n values, positioning will start at n in the segment Tree
            here it runs as st[pos/2]=st[pos] + st[pos +/-1]
            *here is pos is even that means its the right child else right child
            *pos^1 gives us one+ if pos is even, and one- if pos is odd
        */
        for(st[pos+=n]=value;pos>1;pos>>=1) st[pos>>1]=(st[pos] + st[pos^1])%mod;
    }

    //Query in the ranged interval [l,r)
    int query(int l,int r){
        /** The thing is quite complicated here. As mentioned before, current position is odd means its the right child,
            and current position even means its the left child.
            So in the interval [l,r) we have to include l and exclude r

            Here, if l is a left child then we don't have to include that, we can get the sum of itself and its sibling from the parent node
            but if l is not left child then we include it in the sum and increase its value, so that l>>i or l/2 gives us the right next sum
            same case for r, but in vice versa.

            If r is the left child , we don't include it. remember? we've to exclude it from summation? so we use --r and
            dividing it will give us it's left most siblings summation value;

        */
        int ans=0;
        //debug
        for(l+=n,r+=n;l<r;l>>=1,r>>=1){
            if(l&1) ans=(ans+st[l++])%mod;
            if(r&1) ans=(ans + st[--r])%mod;
        }
        return ans;
    }
  
    //Adding value at pos. Here, segmentTree[pos]= sum(from 0 to pos-1) +1
    void addVal(int pos){
        update(pos,query(0,pos)+1);
    }
    
    //getting the result
    int get(){
        return st[1];
    }
    
    //Printing the segmentTree
    void print(){
        for(int i=0;i<len;i++) cout<<st[i]<<" ";
        cout<<endl;
    }
};


//Compare two elements e1, e2 by their data, if data is same then compare if e1 comes after e2 or not
bool compare(element e1,element e2){
    return e1.data<e2.data?true:(e1.data==e2.data?(e1.index>e2.index?true:false):false);
}

int main()
{
    int test,n,len;
    element *arr;
    sf("%d",&test);
    segmentTree *st;

    for(int tc=1;tc<=test;tc++){
        sf("%d",&n);
        arr=new element[n +1];

        for(int i=0;i<n;i++) sf("%d",&arr[i].data), arr[i].index=i;

        st=new segmentTree(n);
        sort(arr,arr+n,compare);
        //for(int i=0;i<n;i++) cout<<arr[i].data<< "-> "<<arr[i].index<<endl;
        for(int i=0;i<n;i++) st->addVal(arr[i].index);
        //st->print();
        pf("Case %d: %d\n",tc, st->query(0,n)%mod);

        free(st),free(arr);
    }


    return 0;
}
/**
Input-output:

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

1 8
1 2 3 3 2 4 3 4
ans=53

*/
