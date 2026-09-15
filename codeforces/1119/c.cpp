#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long ll;
ll a,b;


void solve(){
    ll a,b;
    cin>>a>>b;
    ll x=0;
    ll y=0;
    ll ans=a+b;
    for(int i=30;i>=0;--i){
        if(ans>>i&1){
            ll tem=1<<i;
            if(x+tem<=a)x+=tem;
            else y+=tem;
        }
    }
    cout<<ans<<" "<<(a-x)<<"\n";
}

int main(){
    int tt;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}