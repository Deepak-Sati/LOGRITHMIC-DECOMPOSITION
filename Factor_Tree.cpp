#include <bits/stdc++.h>
using namespace std;

#define  flash ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define  ll long long
#define  endl "\n"
#define  MOD 1000000007

const int maxN = 1e5+5, maxA = 1e6+5, DPN = 20;
int blk, timer, n, q;

vector< vector<int> > g;
ll  ans_query[maxN], inv[20*maxN], ans;

int spf[maxA], a[maxN], cnt[maxA], vis[maxN], lvl[maxN];
int id[2*maxN], tin[maxN], tout[maxN];
int dp[maxN][DPN];

// Query class for Mo's Algorithm
struct Query
{
	int l, r;
	int lca, ind;
	bool operator < (const Query &q1)
	{
	    if(l/blk != q1.l/blk)
	       return l < q1.l;
	    else
	       return l/blk % 2 ? r < q1.r : r > q1.r;
        }
}qr[maxN];

// DFS for in-out time of node and dp for binary Lifting
void dfs(int c,int p)
{
    tin[c]      =  ++timer;
    id[timer]   = c;
    dp[c][0]    = p;
    lvl[c]      = lvl[p] + 1;

    for( int i = 1; i < DPN; i++ )
       dp[c][i] = dp[dp[c][i-1]][i-1];
    
    for( auto k:g[c] )
        if(k != p)
          dfs(k,c);
    tout[c] = ++timer;
    id[timer]   = c;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

// Lowest common ancestor using Binary lifting
int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for ( int i = DPN-1; i >= 0; --i ) 
    {
        if (!is_ancestor(dp[u][i], v))
            u = dp[u][i];
    }
    return dp[u][0];
}

// prime seive of eratosthenes
void precompute()
{
    for( int i = 1; i < maxA; i++ )
        spf[i] = i;
	
    for( int i = 2; i*i < maxA; i++ )
        if( spf[i] == i )
           for( int j = i*i ; j < maxA; j+=i )
               if( spf[j] == j )
                  spf[j] = i;
    
	inv[0] = inv[1] = 1;
  	for( int i = 2; i < 20*maxN; i++ )
	      inv[i] = (MOD - (((MOD/i) * 1ll *inv[MOD % i])  % MOD)) % MOD;
}

// For adding/removing factors of number
void factorise(int ind, int add)
{
    int x = a[ind], p = -1;
    while( x!=1 )
    {
          if(p != spf[x]){
             ans = ( ans * inv[cnt[spf[x]]+1] ) % MOD;
             if(p != -1)
                ans = ( ans * ( cnt[p]+1 ) ) % MOD;
             p = spf[x];
          }
          if(add)
            ++cnt[spf[x]];
          else
            --cnt[spf[x]];
          x /= spf[x];
    }
    ans = ( ans * ( cnt[p]+1 ) ) % MOD;
}

// Remove duplicates using !
void update(int x)
{
    vis[x] = !vis[x];
    factorise(x, vis[x]);
}

// Standard Mo's Algorithm
void MO(int q)
{
        int ml=0,mr=-1;
  	for( int i = 0 ; i < q ; i++ ) 
	{
		int L   = qr[i].l;
		int R   = qr[i].r;

		while(L < ml)	 update(id[--ml]);
		while(R > mr)	 update(id[++mr]);
		while(L > ml)    update(id[ml++]);
                while(R < mr)	 update(id[mr--]);

		int u = id[ml], v = id[mr];
		if( qr[i].lca != u && qr[i].lca != v)
                   update(qr[i].lca);

		ans_query[qr[i].ind] = ans;

		if( qr[i].lca != u && qr[i].lca != v)
                   update(qr[i].lca);
    }
}

void solve()
{
    cin>>n;
    g = vector<vector<int> >(n);
    timer=0;
    for( int i = 0 ; i < n-1 ; i++)
    {
        int u,v; cin >> u >> v;
        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }
    for(int i=0;i<n;i++) 
        cin >> a[i];
    
    dfs(0,0);
    cin >> q;
    
    for( int i = 0 ; i < q; i++ )
    {
        int u,v;cin>>u>>v;
        --u;--v;
        
	qr[i].ind = i;
        qr[i].lca = lca(u,v);
        
	//debug1(qr[i].lca);
        if(tin[u] > tin[v])
            swap(u,v);
        if(qr[i].lca == u)
	{
            qr[i].l = tin[u];
            qr[i].r = tin[v];
        }
        else{
            qr[i].l = tout[u];
            qr[i].r = tin[v];
         }
    }
    
    blk = sqrt(timer+1);
    sort(qr,qr+q);
    memset(cnt,0,sizeof(cnt));
    memset(vis,0,sizeof(vis));
    ans=1;
    MO(q);
    for( int i = 0; i < q; i++ )
        cout << ans_query[i] << endl;
}

int main()
{
flash;
int t;cin>>t;
// Seive for smallest prime factor
	
precompute();                                
while(t--)
    solve();
return 0;
}
