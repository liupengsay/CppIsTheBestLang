#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=5e5+9;
typedef pair<int,int> pii;

inline long long read() {
    register long long x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,m,su[N],sv[N],id[N],sz[N],tot[N],deg[N];
vector<int>e[N],c[N];
vector<pii>ans;

int find(int i) {return id[i]==i?i:id[i]=find(id[i]);}
void add(int u,int v) {
	e[u].push_back(v), e[v].push_back(u);
	id[find(u)]=find(v);
	deg[u]++, deg[v]++;
}

void topo(int u) {
	queue<int>q;
	for(auto v:c[u]) if(deg[v]==1) q.push(v);
	while(!q.empty()) {
		int u=q.front(); q.pop();
		for(auto v:e[u]) {
			deg[v]--;
			if(deg[v]==1) q.push(v);
		}
	}
}

int main() {
	n=read(), m=read();
	rep(i,1,n) id[i]=i;
	rep(i,1,m) add(su[i]=read(),sv[i]=read());
	rep(i,1,n) sz[find(i)]++, c[id[i]].push_back(i);
	rep(i,1,m) tot[id[su[i]]]++;
	rep(i,1,n) if(id[i]==i) {
		if(tot[i]==sz[i]-1) {
			for(auto u:c[i]) if(deg[u]==1) ans.push_back(pii(u,e[u][0]));
		} else {
			topo(i);
			for(auto u:c[i]) if(deg[u])
				for(auto v:e[u]) if(deg[v]==1) ans.push_back(pii(u,v));
		}
	}
	sort(ans.begin(),ans.end());
	printf("%d\n",ans.size());
	for(auto x:ans) printf("%d %d\n",x.first,x.second);
	return 0;
}