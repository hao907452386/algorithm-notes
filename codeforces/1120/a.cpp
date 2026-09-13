#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long ll;

void solve(){
    int n;
    cin>>n;
    int cnt1=0;
    int cnt0=0;
    for(int i=1;i<=n;++i){
        int x;
        cin>>x;
        if(x)cnt1++;
        else cnt0++;
    }
    if(cnt1>=cnt0)cout<<"Bessie\n";
    else cout<<"Elsie\n";
}


int main(){
    int tt;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
