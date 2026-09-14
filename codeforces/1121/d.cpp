#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;


typedef long long ll;
const int N=200010;


int n;

int ans[N];

void solve(){
    cin>>n;
    for(int i=1;i<=n;++i){
        ans[i]=0;
    }
    int len=(n+1)/3;
    if(len%2==1&&len*3==(n+1)){
        ans[1]=1;
        ans[1+len]=1;
        ans[1+len+len-1]=1;
    }
    else{
        int a=len;
        int b=len;
        int c=len;
        int sum=n+1-a-b-c;
        if(sum&&b%2==1)b++,sum--;
        if(sum)a++,sum--;
        if(sum)c++,sum--;
        ans[a]=1;
        ans[a+b]=1;
    }
    for(int i=1;i<=n;++i){
        cout<<ans[i];
    }
    cout<<"\n";
}

int main(){
    int tt;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
