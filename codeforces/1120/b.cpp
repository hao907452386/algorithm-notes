#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long ll;

const int N=1010;
int n,k;
int a[N][N];

void solve(){
    cin>>n>>k;
    int cnt=0;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            a[i][j]=++cnt;
        }
    }
    if(k>=n&&k<=2*n-1){
        int num=2*n-1-k;
        for(int i=0;i<num;++i){
            int tem=2+i;
            swap(a[tem][tem],a[1][tem]);
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
    }else cout<<"-1\n";
}


int main(){
    int tt;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
