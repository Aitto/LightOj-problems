#include<stdio.h>
#include<iostream>
#include<cmath>
#include<stdlib.h>

#define sf scanf
#define pf printf

using namespace std;

int main(){

    //freopen("in.txt", "r",stdin );

    int test,n,m;

    sf("%d",&test);

    for(int i=1;i<=test;i++){
        sf("%d %d",&n,&m);

        int arr[n];
        char task;
        int x,y;

        for(int j=0;j<n;j++){
            sf("%d",&arr[j]);
        }

        for(int j=0;j<m;j++){
            cin>>task;

            switch(task){
                case 'S':{
                    cin>>x;
                    for(int k=0;k<n;k++){
                        arr[k]+=x;
                    }
                    break;
                }
                case 'M':{
                    cin>>x;
                    for(int k=0;k<n;k++){
                        arr[k]=arr[k]*x;
                    }
                    break;
                }
                case 'D':{
                    cin>>x;
                    for(int k=0;k<n;k++){
                        arr[k]=arr[k]/x;
                    }
                    break;
                }
                case 'R':{
                    int temp;
                    int l=n-1,r;
                    r=l;
                    l=(l-1)/2;
                    for(int k=0;k<=l;k++){
                        temp=arr[k];
                        arr[k]=arr[r-k];
                        arr[r-k]=temp;
                    }
                    break;
                }

                case 'P':{
                    int temp;
                    cin>>x>>y;
                    temp=arr[x];
                    arr[x]=arr[y];
                    arr[y]=temp;
                    break;
                }

            }
            /*for(int k=0;k<n;k++){
                pf("%d ",arr[k]);
            }
            cout<<endl;*/
        }
        pf("Case %d:\n",i);
            for(int j=0;j<n;j++){
                    if(j!=n-1)
                        pf("%d ",arr[j]);
                    else pf("%d",arr[j]);
            }

        pf("\n");
    }

    return 0;
}
