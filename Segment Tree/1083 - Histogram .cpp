/*
Algo for finding the largest rectangle in O(n) time
*/
/*
Author @Aitto_sang
CSE@Buet
*/
#include<stdio.h>
#include<iostream>
//#include<ctime>
//#include<cmath>
//#//include<cstdlib>
//#include<algorithm>
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

class Stack{
private:
    int length;
    int index;
    int *arr;
public:
    Stack(int n){
        int length=n;
        index=0;
        arr=new int[n +1];
    }

    void push(int n){
        if(length==index){
            int *temp;
            length*=2;
            temp=new int[length];
            for(int i=0;i<index;i++){
                temp[i]=arr[i];
            }
            arr=temp;
        }

        arr[index]=n;
        index++;
    }

    int pop(){
        if(index==0) return -1;
        index--;
        return arr[index];
    }

    bool isEmpty(){
        if(index==0) return true;
        return false;
    }

    int top(){
        if(index==0) return -1;
        return arr[index-1];
    }

    int getLength(){
        return length;
    }

};

int calcRectangle(int *arr,int len){
    Stack position(len), height(len);
    int area=0,temp,h,tempPos;
    for(int i=0;i<len;i++){
        h=arr[i];
        //At first or whenever we get a height greater than the last height
        //Getting a greater height means that we are starting a new rectangle and, we have to keep track of that
        if(i == 0 or h > height.top() ){
            position.push(i);
            height.push(h);
        }else if( h < height.top()){
            //Pop everything larger than that height and add the new height
            // we add last position because, if that is the smallest or equal then
            //that height was started at the last position
            while( !height.isEmpty() and h< height.top() ){
                tempPos=position.pop();
                temp=height.pop()*(i-tempPos);
                if(area< temp) area=temp;
            }
            height.push(h);
            position.push(tempPos);
        }
    }
    //Keep counting till the stack is not empty
    while(!height.isEmpty()){
        tempPos=position.pop();
        temp=height.pop()*(len-tempPos);
        if(area< temp) area=temp;
    }
    //cout<<area<<endl;
    return area;

}

int main()
{
    syncronize
    readFile

    int test,n;
    cin>>test;
    int *arr;

    for(int tc=1;tc<=test;tc++){
        cin>>n;
        arr=new int[n +1];

        for(int i=0;i<n;i++) cin>>arr[i];

        cout<< "Case "<<tc<< ": "<<calcRectangle(arr,n)<<endl;
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
