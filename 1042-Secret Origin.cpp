#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cmath>


#define sf scanf
#define pf printf
#define Minus_Infinite -99999999
#define Minus_Long_Infinite -999999999999999

using namespace std;

long long int seek(long long int n){

    int c=0,zeroes=0,ones=0,oneIndex=0;
    long long int mask=1;
    bool flag=true;

    for(int i=0;i<31;i++){
        if( (n&mask)!=0 ){
            // seeks first occurrence of one
            if(flag){
                oneIndex=i;
                flag=false;
            }

            if((n&(mask<<1))==0){
                ones++;
                c=i;
                break;
            }


            ones++;
        }else{
            zeroes++;
        }
        mask=mask<<1;
    }
    //mask=1;
    //cout<< "zeroes: "<<zeroes<< " ones: "<<ones<< " OneIndex: "<<oneIndex<<endl;;

    if(zeroes==0 || ones==0) return n+mask;
    else{
        mask=1;
        /*if(zeroes>ones){
            mask=mask<<oneIndex-zeroes;
            while(--ones){
                mask=mask<<1;
                mask+=1;
            }
        }else*/ if(zeroes>=ones){
            mask=mask<<oneIndex +1-ones;
            while(--ones){
                mask=mask<<1;
                mask+=1;
            }
        }else{
            mask=mask<<ones-zeroes-1;
            //cout<<mask<<endl;
            while(zeroes--){
                mask=mask<<1;
                mask+=1;
                //cout<<mask<<endl;
            }
        }

        return n+mask;
    }


}


int main(){

    long long int num;
    int test;

    sf("%d",&test);

    for(int i=1;i<=test;i++){
        sf("%lld",&num);
        pf("Case %d: %d\n",i,seek(num));
    }

    return 0;
}

