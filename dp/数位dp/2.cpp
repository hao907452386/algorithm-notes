

//题意描述
//定义数列f，满足f(1)=1，且3*f(n)*f(2n+1)=f(2n)*(1+3*f(n))，f(2n)<6*f(n)
//给定n和P，定义g(k)为[1,n]中满足f(i)%P=k的i的个数
//要求g(0)^g(1)^...^g(P-1)
//由原式可以推出f(2n)=3*f(n)，f(2n+1)=3*f(n)+1
//因此f(n)等价于把n的二进制表示直接看成三进制数
//问题转化为：统计[1,n]中所有数的二进制表示看成三进制后，模P得到各余数的方案数


//如果最终求的取模值是一样的，那么dfs到u为0直接判断cur是否是给定的k去是否返回1，
//之后就是常规的dfs，但是这道题目，我们需要同时求出若干个k的数量，因此当dfs到0的时候我们只能gcur加加，
//你的dfs本质是个for循环很简单的一个，但是可能会忘记递归到终点判断，所以写成dfs是好的，
//之后看每个位置，前面全部是贴着上界写的，假设正在比较第pos位置，之前是cur，cur是前面的数值，
//最低位是pos加一位，所以得乘以3的pos算成正确的权重，之后我们需要什么呢、
//需要的是dp pos mod 表示还剩下pos位置随便填，余数是mod的方案数，之后加贴着上界的答案计算到最终结果g nmod上，
//所以每层复杂度是p、最终复杂度是logn 乘以p、完美解决


#include<iostream>
#include<cstring>
using namespace std;

typedef long long ll;
const int N=70;
const int M=65540;

ll n;
int P,len,num[N],pw[N];
ll dp[N][M],g[M];

void dfs(int pos,int cur){
	if(!pos){
		g[cur]++;
		return;
	}

	if(num[pos]){
		// 当前位把 n 的 1 改成 0
		// 后面的 pos-1 位随便填
		for(int r=0;r<P;++r){
			if(!dp[pos-1][r])continue;
			int nr=((ll)cur*3%P*pw[pos-1]+r)%P;
			g[nr]+=dp[pos-1][r];
		}

		// 当前位仍然填 1，继续贴着 n
		dfs(pos-1,((ll)cur*3+1)%P);
	}
	else{
		// n 当前位是0，只能继续填0
		dfs(pos-1,(ll)cur*3%P);
	}
}

int main(){
	cin>>n>>P;

	ll x=n;
	while(x){
		num[++len]=x&1;
		x>>=1;
	}

	pw[0]=1%P;
	for(int i=1;i<=len;++i)
		pw[i]=(ll)pw[i-1]*3%P;

	dp[0][0]=1;
	for(int i=1;i<=len;++i){
		for(int r=0;r<P;++r){
			if(!dp[i-1][r])continue;
			dp[i][r*3%P]+=dp[i-1][r];
			dp[i][(r*3+1)%P]+=dp[i-1][r];
		}
	}

	dfs(len,0);

	// dfs统计的是 [0,n]
	// 去掉数字0
	g[0]--;

	ll ans=0;
	for(int i=0;i<P;++i)ans^=g[i];

	cout<<ans<<'\n';
	return 0;
}

//如果只求单一mod值k：
//dfs(pos,cur,lim)表示当前处理到第pos位，前面对应三进制值模P为cur，且是否贴着上界
//当pos=0时，直接判断cur是否等于目标k，是则返回1，否则返回0
//因为最终只关心一个固定余数，所以每个状态只需要返回一个方案数，可以直接记忆化
//若lim=0，后面已经不受上界限制，此时dp[pos][cur]可以直接记忆化
//转移时当前二进制位填b，则新的余数为(cur*3+b)%P
//由于允许前导0，所以会把数字0也统计进去，若k=0最后需要减去1
//复杂度O(logn*P)

#include<iostream>
#include<cstring>
using namespace std;

typedef long long ll;
const int N=70;
const int M=65540;

ll n;
int P,k,len,num[N];
ll dp[N][M];

ll dfs(int pos,int cur,int lim){
	if(!pos)return cur==k;

	if(!lim&&dp[pos][cur]!=-1)
		return dp[pos][cur];

	int up=lim?num[pos]:1;
	ll res=0;

	for(int b=0;b<=up;++b){
		int ncur=((ll)cur*3+b)%P;
		res+=dfs(pos-1,ncur,lim&&(b==up));
	}

	if(!lim)dp[pos][cur]=res;
	return res;
}

int main(){
	cin>>n>>P>>k;

	ll x=n;
	while(x){
		num[++len]=x&1;
		x>>=1;
	}

	memset(dp,-1,sizeof dp);

	ll ans=dfs(len,0,1);

	// dfs统计的是[0,n]，若k=0则数字0被多算了一次
	if(k==0)ans--;

	cout<<ans<<'\n';
	return 0;
}
