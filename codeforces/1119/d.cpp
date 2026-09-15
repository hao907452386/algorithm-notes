#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;


typedef long long ll;

const int off=3,inf=1e9;
const int N=300010;
int dp[N][7];
int n;


void solve(){
    cin>>n;
    string s;
    cin>>s;
    s=" "+s;
    for(int i=0;i<=n;++i){
        for(int j=0;j<7;++j){
            dp[i][j]=inf;
        }
    }
    dp[0][0+off]=0;
    for(int i=1;i<=n;++i){
        for(int j=-3;j<=3;++j){
            if(s[i]=='+'&&j<=0)continue;
            if(s[i]=='-'&&j>=0)continue;
            if(s[i]=='0'&&j!=0)continue;
            for(int k=-3;k<=3;++k){
                if(j==k)continue;
                dp[i][j+off]=min(dp[i][j+off],max(dp[i-1][k+off],abs(k-j)));
            }
        }
    }
    int ans=inf;
    for(int j=0;j<7;++j)ans=min(ans,dp[n][j]);
    if(ans==inf)cout<<"-1\n";
    else cout<<ans<<endl;
}


int main(){
    int tt;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}