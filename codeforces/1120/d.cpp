#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long ll;
const int N=100010;
const int mod=1e9+7;

//问题转化是简单的
//0到n-1的值域上有若干个区间必须选一个数，有若干个区间必须全都不选
//区间全都不选的处理是用差分处理，容易想到
//但是区间选难处理
//首先其实区间不会很多，因为后期区间很大，而我们关注的区间范围是0到n-1
//每个k都有n/k个区间，调和级数完全可以全部处理
//接下来讲解如何处理区间至少选择一个数字
//定义dp[i+1]为最后一次选择的数字是i的方案数字
// 朴素转移：若 i 可以选，则 dp[i+1] 等于处理 i 之前所有合法状态的方案数之和
//对于l到r必选选一个数字可以转化为构造到r是最后一个选择的数字必须大于等于l
//这样最后再次求一个前缀最大值就可以将条件转化
//最阴间的一点在于如果r>n-1我们需要强制取n-1,否则这个条件相当于没有考虑
//之后转移dp[i+1]=sum(dp[j+1])其中j>=minn[i-1](i-1看下面)
//如果暴力是n2超时
//所以考虑维护sum表示当前合法dp的和
//转移的时候是先转移dp[i+1]=sum(d[i]==0)相当于之前合法最后放上i也合法
//之后由于i限制的加入有些解会变得不合法所以再去减法
//每次右移都会minn[i]都不会减小
//所以可以用双指针维护解决
//最后答案就是sum

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
            ll l=(ll)k*j;
            ll r=min((ll)n-1,(ll)k*j+k-1);
            minn[r]=max((ll)minn[r],l);
            if(k*j+k-1>=n)break;
        }
        ll l=(ll)k*x;
        ll r=(ll)k*x+k-1;
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
