#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;


typedef long long ll;
const int N=200010;
ll a,b,k;

void solve(){
    cin>>a>>b>>k;
    ll ans=0;
    ll tem=b-a;
    for(int i=0;;i++){
        if(k==0){
            cout<<ans<<"\n";
            return;
        }
        ans+=(tem%a+a)%a;
        a++;
        k--;
        if(a>tem)break;
    }
    ans+=k*tem;
    cout<<ans<<"\n";
}

int main(){
    int tt;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}