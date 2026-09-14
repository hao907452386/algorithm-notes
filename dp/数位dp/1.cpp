
//题意描述
//给定区间[A,B]和K，要求所有数位乘积等于K的整数之和，答案对20120427取模
//多组询问，区间答案用cal(B,K)-cal(A-1,K)得到

//思路概括
//使用数位DP处理1~x中数位积等于K的所有数字之和
//dfs(u,k,f0,lim)：当前还剩u位，需要后续数位乘积凑出k
//返回cnt和sum，分别表示合法方案数和这些数字的数值和
//转移时若仍处于前导零阶段，0不参与乘积；否则当前位i必须非0且整除k，递归处理k/i
//利用mx[u]=9^u剪枝：若k>9^u，则剩余u位不可能凑出乘积k
//非受限且已经开始数字后，用unordered_map记忆化状态(u,k)，减少重复计算
//K=0单独处理：记录是否已经出现过非前导零的0，只要出现过一次，整个数位积就是0
//同时维护pw[i]=10^i，用t.sum+i*10^(u-1)*t.cnt计算当前位对数字和的贡献
//若K含有2、3、5、7之外的质因子，则不可能由十进制数位乘积得到，答案直接为0



#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

typedef long long ll;
const int mod=20120427;
const int N=20;

struct Node{
	int cnt,sum; // 合法后缀个数、后缀数值和，均取模
};

int num[N];
ll pw[N],mx[N]; // 10^i取模、9^i
int p[4]={2,3,5,7};
unordered_map<ll,Node> dp[N];
Node f[N][2];
bool vis[N][2];

void add(int& x,ll y){
	x=(x+y)%mod;
}

// 剩余u位，需要凑出的乘积为k
Node dfs(int u,ll k,int f0,int lim){
	if(k>mx[u])return {0,0}; // u位的乘积最大为9^u
	if(!u)return {k==1&&!f0,0};

	if(!f0&&!lim){
		auto it=dp[u].find(k);
		if(it!=dp[u].end())return it->second;
	}

	int up=lim?num[u]:9;
	Node res={0,0};

	for(int i=0;i<=up;++i){
		Node t;
		if(f0&&i==0){
			// 前导零不参与乘积
			t=dfs(u-1,k,1,lim&&i==up);
		}else{
			// 正乘积不能包含0，且当前数字必须整除k
			if(!i||k%i)continue;
			t=dfs(u-1,k/i,0,lim&&i==up);
		}

		add(res.cnt,t.cnt);
		add(res.sum,t.sum+(ll)i*pw[u-1]%mod*t.cnt);
	}

	if(!f0&&!lim)dp[u][k]=res;
	return res;
}

// K=0：zero表示是否出现过非前导零的0
Node dfs0(int u,int zero,int f0,int lim){
	if(!u)return {zero&&!f0,0};
	if(!f0&&!lim&&vis[u][zero])return f[u][zero];

	int up=lim?num[u]:9;
	Node res={0,0};

	for(int i=0;i<=up;++i){
		int nf0=f0&&i==0;
		int nz=zero||(!f0&&i==0);
		Node t=dfs0(u-1,nz,nf0,lim&&i==up);

		add(res.cnt,t.cnt);
		add(res.sum,t.sum+(ll)i*pw[u-1]%mod*t.cnt);
	}

	if(!f0&&!lim){
		vis[u][zero]=1;
		f[u][zero]=res;
	}
	return res;
}

// 计算1~x中数位积等于k的编号和
int cal(ll x,ll k){
	if(x<=0)return 0;

	string s=to_string(x);
	int len=0;
	for(int i=(int)s.size()-1;i>=0;--i)
		num[++len]=s[i]-'0';

	if(!k)return dfs0(len,0,1,1).sum;
	return dfs(len,k,1,1).sum;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	pw[0]=mx[0]=1;
	for(int i=1;i<N;++i){
		pw[i]=pw[i-1]*10%mod;
		mx[i]=mx[i-1]*9;
	}

	int n;
	ll A,B,K;
	cin>>n;

	while(n--){
		cin>>A>>B>>K;

		// 非零数位积只能含有质因子2、3、5、7
		ll t=K;
		if(t){
			for(int i=0;i<4;++i)
				while(t%p[i]==0)t/=p[i];
		}
		if(t>1){
			cout<<0<<'\n';
			continue;
		}

		cout<<(cal(B,K)-cal(A-1,K)+mod)%mod<<'\n';
	}
	return 0;
}
