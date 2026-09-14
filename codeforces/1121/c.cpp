#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long ll;
const int N=200010;
const int mod=998244353;

ll a[N];
int n;
ll fact[N];


ll qmi(ll a,ll k,ll p){
    ll res=1;
    while(k){
        if(k&1)res=res*a%p;
        a=a*a%p;
        k/=2;
    }
    return res;
}

ll inv(ll x){
    return qmi(x,mod-2,mod);
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    ll ans=0;
    fact[0]=1;
    for(int i=1;i<=n-1;++i)fact[i]=fact[i-1]*i%mod;
    sort(a+1,a+n+1);
    ll sum=a[n];
    for(int i=n-1;i>=1;--i){
        ll tem=fact[n-1]*inv(n-i)%mod;
        ans=(ans+tem*(sum-(n-i)*a[i]%mod)%mod)%mod;
        sum=(sum+a[i])%mod;
    }
    cout<<(ans%mod+mod)%mod<<endl;
}


int main(){
    int tt;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
