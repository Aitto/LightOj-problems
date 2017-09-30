#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cmath>


#define sf scanf
#define pf printf

using namespace std;


int main(){

    int test;
    sf("%d",&test);

    int row,col,ans,c;

    for(int i=1;i<=test;i++){
        sf("%d %d",&row,&col);

        if(row==1 || col==1) ans=row*col;
        else if( row==2 || col==2){
            c=row*col;
            if(c%8==4) ans= (c/4) * 2 + 2;
            else ans= (c/4) *2 + c%4;
        }else{
            c=row*col;
            ans=(c+1)/2;
        }

        pf("Case %d: %d\n",i,ans);

    }

    return 0;
}
