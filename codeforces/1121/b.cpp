#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<set>
using namespace std;

typedef long long ll;
const int N=200010;

ll a[N];
int n,m;


void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    ll ans=-1e18;
    ll sum=0;
    ll minn=0;
    multiset<int>s;
    for(int i=1;i<=n;++i){
        if(s.size()>=m-1){
            ans=max(ans,sum+m*a[i]);
        }
        s.insert(-a[i]);
        sum+=-a[i];
        if(s.size()>=m){
            auto it=s.begin();
            sum-=*it;
            s.erase(it);
        }
    }
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
