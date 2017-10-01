#include<stdio.h>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>

#define pf printf
#define sf scanf
#define pi acos(-1.0)

using namespace std;

int main(){

    int test,n;
    double theta,R,r,angle;

    sf("%d",&test);

    for(int i=1;i<=test;i++){
        sf("%lf %d",&R,&n);

        theta=(double)(pi/n);
        angle=sin(theta);
        r=(angle*R)/(1+angle);

        if(floor(r)==r) pf("Case %d: %d\n",i,(int)r);
        else pf("Case %d: %.10f\n",i,r);

    }

    return 0;

}
