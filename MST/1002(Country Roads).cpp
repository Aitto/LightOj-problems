#include<stdio.h>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<stack>
#include<cstring>

#define lli long long int
#define pf printf
#define sf scanf
#define pi 3.141592653589793116
#define inf 99999999
#define maxInt 99999999
#define maxNEG -99999999.0
#define debug cout<<"Hello here!"<<endl;
#define readFile freopen("in.txt","r",stdin);

using namespace std;

class Element{
public:
    int data;
    int key;

    Element(int a=0,int b=inf){
        data=a;
        key=b;
    }

};

class MinHeap{
    Element *arr;
    int length;
    int nVertices;
    int *mapping; //Keeping track of data for O(1) access;

public:

    MinHeap(int n){
        nVertices=n;
        length=0;
        arr=new Element[nVertices +1];
        mapping =new int[505]; //At most 500 vertices
        for(int i=0;i<505;i++) mapping[i]=-1;
    }

    void Update(int d,int k){
        int index=mapping[d];
        if(index==-1 or index>nVertices) return;

        if(arr[index].key >k ){
            arr[index].key=k;
            buHeapify(index);
        }else{
            arr[index].key=k;
            Heapify(index);
        }
    }

    void add(int d,int k){
        if(length >= nVertices) {
            nVertices*=2;

            Element *temp;
            temp=new Element[nVertices];

            for(int i=1;i<=length;i++) temp[i]=arr[i];
            free(arr);

            arr=temp;

        }
        length++;
        arr[length].data=d;
        arr[length].key=k;

        buHeapify(length);
    }

    //top to bottom
    void Heapify(int n){
        int parent=n;
        int left;
        int right;
        int smallest;

        while(1){

            left=parent*2;
            right=left +1;
            if(left> length) return; //We are done. We are at the bottom
            if(right>length) smallest=left;
            else if( arr[left].key < arr[right].key ) smallest=left;
            else smallest=right;


            if( arr[parent].key <= arr[smallest].key ) break; //we are done heapifying
            Element temp;


            temp=arr[parent];
            arr[parent]=arr[smallest];
            arr[smallest]=temp;

            mapping[ arr[smallest].data ]=smallest;
            mapping[ arr[parent].data ]=parent;

            parent=smallest;

        }

    }

    //From bottom to top
    void buHeapify(int n){
        int child=n;
        int parent=child/2;

        while(parent){

            if( arr[parent].key < arr[child].key ) return; //We are done

            Element temp;
            temp=arr[parent];
            arr[parent]=arr[child];
            arr[child]=temp;

            mapping[ arr[parent].data ]=parent;
            mapping[ arr[child].data ]=child;

            child=parent;
            parent=child/2;
        }

    }

    void printHeap(){
        cout<< "printing********"<<endl;
        for(int i=1;i<=length;i++) pf("%d %d\n",arr[i].data,arr[i].key);
        cout<< "Complete*********"<<endl;
    }

    int getMin(){
        if(length==0) return -1;
        return arr[1].data;
    }

    int removeMin(){
        if(length==0) return -1;
        Element temp;
        temp=arr[1];
        arr[1]=arr[length];
        length--;
        Heapify(1);
        return temp.data;
    }

    bool isEmpty(){
        if(length==0) return true;
        return false;
    }

};

int main(){

    //readFile

    int **arr,n,m,*ans,*visit,t,u,v,w,s,*dis,*p,track;

    sf("%d",&t);

    for(int tc=1;tc<=t;tc++){
        MinHeap mh(1000);

        //Input number of vertices and edges
        sf("%d %d",&n,&m);

        //Allocate memory
        arr=new int*[n +1];
        ans=new int[n +1];
        visit=new int[n +1];
        dis=new int[n +1];
        p=new int[n +1];


        //Allocate memory and initialize
        for(int i=0;i<n;i++){
            arr[i]=new int[n +1];
            visit[i]=0;
            dis[i]=inf;
            p[i]=-1;
            for(int j=0;j<n;j++){
                arr[i][j]=inf;
            }
        }

        //Input array
        for(int i=0;i<m;i++){
            sf("%d %d %d",&u,&v,&w);
            if(arr[u][v] > w){
                arr[u][v]=w;
                arr[v][u]=w;
            }
        }

        //Source input
        sf("%d",&s);

        //prims algorithm
        mh.add(s,0);
        p[s]=s;
        int temp;

        while(!mh.isEmpty()){
            temp=mh.removeMin();

            if(temp==-1) break;
            if(visit[temp]==1) continue;
            for(int i=0;i<n;i++){
                if( arr[temp][i]!=inf and( arr[temp][i] < dis[i] ) and visit[i]==0 ){
                    mh.add(i,arr[temp][i]);
                    dis[i]=arr[temp][i];
                    p[i]=temp;
                }
            }
            visit[temp]=1;
        }

        //Print answer
        pf("Case %d:\n",tc);
        track=0;
        //for(int i=0;i<n;i++) if(p[i]!=-1) pf("%d %d\n",i,p[i]); debug

        for(int i=0;i<n;i++){
            int parent=i,temp;
            int mx=0;

            while(1){
                parent=p[temp=parent];
                if(parent==-1){
                    track=1;
                    break;
                }
                if(arr[parent][temp]>mx) mx=arr[parent][temp];
                if(parent==s) break;
            }
            if(track) {
                pf("Impossible\n");
                track=0;
            }
            else{
                if(mx==inf) mx=0;
                pf("%d\n",mx);
            }
        }

        /*for(int i=0;i<n;i++)
        for(int j=i;j<n;j++){
            if(ans[i][j]!=inf) pf("%d %d %d\n",i,j,ans[i][j]);
        }*/

        free(p);
        free(arr);
        free(dis);
        free(visit);


    }


    return 0;
}

/**
1 9 9
1 7 4

*/
