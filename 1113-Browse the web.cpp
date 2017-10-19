#include<stdio.h>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<stack>
#include<cstring>

#define pf printf
#define sf scanf
#define pi 3.141592653589793116
#define INF 99999
#define maxInt 99999999
#define maxNEG -99999999.0
#define debug cout<<"Hello here!"<<endl;
#define readFile freopen("in.txt","r",stdin);

using namespace std;

int match(string str){

    if(str[0]== 'Q') return 0;
    if(str[0]=='V') return 1;
    if(str[0]=='B') return 2;
    if(str[0]=='F') return 3;

    return -1;
}

int strcmp(string a,string b){
    int l=a.length();
    if(a.length()!= b.length()) return -1;

    for(int i=0;i<l;i++){
        if(a[i]==b[i]);
        else return a[i]-b[i];
    }
    return 0;
}

int main(){
    readFile

    int t,k;
    sf("%d",&t);

    string web,key;

    for(int i=1;i<=t;i++){
        stack<string> track1,cur,track2;
        track1.push("http://www.lightoj.com/");
        pf("Case %d:\n",i);
        bool flag=false;

        while(true){

            cin>>key;
            k=match(key);

            switch(k){
                case 0:{
                    flag=true;
                    break;
                }
                case 1:{ //visit
                    cin>>web;
                    cout<<web<<endl;

                    if(!cur.empty()){
                        //Checking if same website is visited simultaneously  twice or more!
                        if( strcmp(web,cur.top()) == 0 ) break;

                        track1.push( cur.top() );
                        cur.pop();
                    }

                    //Making forward stack empty as new Web is visited
                    stack<string> tmp;
                    track2=tmp;

                    cur.push(web);
                    break;
                }
                case 2:{ //Backward
                    if(track1.empty()){
                        pf("Ignored\n");
                        break;
                    }
                    //Retrieving previous visited web address
                    web=track1.top();
                    track1.pop();

                    //showing previous web address
                    cout<<web<<endl;

                    if(!cur.empty()){
                        //Pushing current web address to forward stack
                        track2.push(cur.top());
                        cur.pop();
                    }
                    cur.push(web);
                    break;
                }
                case 3:{ //Forward
                    if(track2.empty()){
                        pf("Ignored\n");
                        break;
                    }

                    //Retrieving wev address from forward stack
                    web=track2.top();
                    track2.pop();

                    cout<<web<<endl;

                    if(!cur.empty()){
                        // pushing current address to back stack
                        track1.push(cur.top());
                        cur.pop();
                    }
                    cur.push(web);
                    break;
                }
            }
            if(flag==true) break;
        }
    }


    return 0;

}
