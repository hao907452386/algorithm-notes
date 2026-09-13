#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

typedef long long ll;


const int N=100010;
int d[N];
int n;

void solve(){
    cin>>n;
    for(int i=0;i<=n;++i)d[i]=0;
    for(int k=1;k<=n;++k){
        int x;
        cin>>x;
        int l=x*k,r=x*k+k-1;
        d[l]++,d[r+1]--;
    }
    vector<int>ans;
    int now=0;
    for(int i=0;i<=n;++i){
        now+=d[i];
        if(now==0)ans.push_back(i);
    }
    cout<<ans.size()<<endl;
    for(int u:ans){
        cout<<u<<" ";
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
