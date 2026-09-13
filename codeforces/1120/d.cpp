#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long ll;
const int N=100010;
const int mod=1e9+7;


typedef long long ll;

int n;
int dp[N];
int minn[N];
int d[N];


void solve(){
    cin>>n;
    for(int i=0;i<n;++i){
        dp[i]=d[i]=0;
        minn[i]=-1;
    }
    for(int k=1;k<=n;++k){
        int x;
        cin>>x;
        for(int j=0;j<x;++j){
            int l=k*j;
            int r=min(n-1,k*j+k-1);
            minn[r]=max(minn[r],l);
            if(r>=n)break;
        }
        int l=k*x;
        int r=k*x+k-1;
        if(l<n)d[l]++;
        if(r+1<n)d[r+1]--;
    }
    for(int i=1;i<n;++i){
        minn[i]=max(minn[i],minn[i-1]);
    }
    dp[0]=1;
    ll ans=1;
    int p=-1;
    for(int i=1;i<n;++i){
        d[i]+=d[i-1];
    }
    for(int i=0;i<n;++i){
        if(d[i]){
            dp[i+1]=0;
        }
        else dp[i+1]=ans;
        ans=(ans+dp[i+1])%mod;
        while(p<minn[i]){
            ans=(ans-dp[p+1])%mod;
            p++;
        }
    }
    ans=(ans%mod+mod)%mod;
    cout<<ans<<endl;
}


int main(){
    int tt;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
