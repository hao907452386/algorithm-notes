#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;


const int N=100010;
typedef long long ll;
int a[N];
int n,m;
int c[N];


void solve(){
    cin>>n;
    m=0;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<=n;++i){
        if(a[i]!=i)c[++m]=i;
    }
    for(int i=1;i<=m/2;++i){
        swap(a[c[i]],a[c[m+1-i]]);
    }
    for(int i=1;i<=n;++i){
        if(a[i]!=i){
            cout<<"NO\n";
            return;
        }
    }
    cout<<"YES\n";
}

int main(){
    int tt;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}