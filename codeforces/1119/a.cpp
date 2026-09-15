#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;


typedef long long ll;
const int N=200010;
int a[N];
int n;

void solve(){
    cin>>n;
    int cnt=0;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        if(i>=2&&i<=n-1&&!a[i])cnt++;
    }
    int ans=(a[1]==1)+(a[n]==1);
    if(ans>cnt)cout<<"-1\n";
    else cout<<ans<<"\n";
}

int main(){
    int tt;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}