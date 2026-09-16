// 题意概述
// 给定 n 根长度为 a_i 的火柴，1 <= a_i <= m，且 n,m <= 20000。
// 一次操作可以选出若干当前存在的火柴，并指定切割长度 x：长度不超过 x 的
// 火柴不变，长度 L>x 的火柴被切成 x 和 L-x 两段。最终只能选择一种固定
// 长度的火柴交给卖家。对 k=1,2,...,m，求至多操作 k 次时能得到的同长火柴
// 的最大数量。

// 题解思路
// 固定操作次数 k 和目标长度 x。对一根长度为 L 的原火柴，它能贡献
// min(floor(L/x), 2^k-1) 根长度为 x 的火柴；当 L=2^k*x 时，还能把剩余
// 部分也恰好切成 x，因此需要额外贡献 1。
//
// 令 suf[t] 表示原火柴中长度至少为 t 的数量。根据
// floor(L/x)>=j <=> L>=j*x，可把所有火柴的基础贡献写成：
//   suf[x] + suf[2*x] + ... + suf[(2^k-1)*x]
// 再加上特殊长度的数量 cnt[2^k*x]，所以
//   res(k,x)=sum_{j=1}^{2^k-1} suf[j*x] + cnt[2^k*x]。
//
// 若分别枚举每个 k，会重复计算前面相同的 suf 项。改为固定 x，只枚举一次
// j=1..floor(m/x)，维护前缀和 tem；当 j=2^k-1 时，就得到当前 k 的基础
// 贡献，再补上 cnt[2^k*x]，并更新 ans[k]。所有 x 的枚举总次数为
// sum_{x=1}^{m} floor(m/x)=O(m log m)。
//
// 当 2^k-1>m 时，目标长度取 1 已足以把每根火柴完全拆开，答案达到理论上限
// sum(a_i)，之后所有更大的 k 的答案也都等于 sum(a_i)。
//
// 时间复杂度：O(n+m log m)；空间复杂度：O(m)。


#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;



const int N=200010;
typedef long long ll;
int n,m;
ll cnt[N];
ll suf[N];
ll pw[21];
ll ans[21];

void solve(){
    cin>>n>>m;
    memset(ans,0,sizeof ans);
    for(int i=1;i<=m;++i){
        cnt[i]=0;
    }
    ll sum=0;
    for(int i=1;i<=n;++i){
        int x;
        cin>>x;
        sum+=x;
        cnt[x]++;
    }
    suf[m]=cnt[m];
    for(int i=m-1;i>=1;--i){
        suf[i]=suf[i+1]+cnt[i];
    }
    int maxn=0;
    for(int x=1;x<=m;++x){
        int k=1;
        ll tem=0;
        for(int j=1;j*x<=m;++j){
            tem+=suf[j*x];
            if(j==pw[k]-1){
                maxn=max(maxn,k);
                ll res=tem;
                if(pw[k]*x<=m)res+=cnt[pw[k]*x];
                ans[k]=max(ans[k],res);
                k++;
            }
        }
    }
    for(int k=1;k<=maxn;++k){
        cout<<ans[k]<<" ";
    }
    for(int k=maxn+1;k<=m;++k){
        cout<<sum<<" ";
    }
    cout<<"\n";
}

int main(){
    pw[0]=1;
    for(int i=1;i<=20;++i){
        pw[i]=pw[i-1]*2;
    }
    int tt;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
