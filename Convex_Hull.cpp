#include<bits/stdc++.h>
using namespace std;

//ORDERED SET
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/trie_policy.hpp>
using namespace __gnu_pbds;
using ordered_set = tree <int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T> ostream& operator<<(ostream &os, ordered_set<T> S){ os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<typename T, typename V = __gnu_pbds::null_type>
using ordered_set_pair = __gnu_pbds::tree<T, V, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

// TEMPLATES
template<typename T> ostream& operator<<(ostream &os, const vector<T> &V) { os << '{'; string sep; for (const auto &x : V) os << sep << x, sep = ", "; return os << '}'; }
template<typename T> ostream& operator<<(ostream &os, const vector<pair<T,T>> &V) { os << '{'; string sep; for (const auto &x : V) os << sep << '(' << x.ff << "," << x.ss << ')', sep = ", "; return os << '}'; }
template<typename A,typename B> ostream& operator<<(ostream &os, const pair<A, B> &P) { return os << '(' << P.first << ", " << P.second << ')'; }
template<typename T> ostream& operator<<(ostream &os, const set<T> &S) { os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<typename T> ostream& operator<<(ostream &os, const unordered_set<T> &S) { os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<typename L,typename R> ostream& operator<<(ostream &os, const map<L,R> &M) { os << "{ ";for(auto m:M) os<<"("<<m.first<<":"<<m.second<<") ";return os<<"}";}
template<typename L,typename R> ostream& operator<<(ostream &os, const unordered_map<L,R> &M) { os << "{ ";for(auto m:M) os<<"("<<m.first<<":"<<m.second<<") ";return os<<"}";}

template<typename x,typename y> x max(x a,y b){return (a>b)?a:b;}
template<typename x,typename y> x min(x a,y b){return (a<b)?a:b;}

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#define DEEPAK
#ifdef  DEEPAK
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

// FUNCTIONS
bool isPrime(int n){if(n<=1)return false;if(n<=3)return true;if(n%2==0||n%3==0)return false;for(int i=5;i*i<=n;i=i+6)
if(n%i==0||n%(i+2)==0)return false;return true;}
const int mod=1e9+7;
inline int add(int x,int y){x+=y;if (x>=mod) return x-mod;return x;}
inline int sub(int x,int y){x-=y;if (x<0) return x+mod;return x;}
inline int mul(int x,int y){return (x*1ll*y)%mod;}
inline int power(int x,int y){int ans=1;while(y){if (y&1) ans=mul(ans,x);x=mul(x,x);y>>=1;}return ans;}
inline int inv(int x){return power(x,mod-2);}
mt19937  RNG(chrono::steady_clock::now().time_since_epoch().count());

// DEFINE
#define  flash ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define  int long long
#define  double long double
#define  endl "\n"
#define  ff first
#define  ss second
#define  gcd(a,b)       __gcd(a,b)
#define  mem(ar)        memset(ar,0,sizeof ar)
#define  ctone(x)       __builtin_popcount(x)
#define  foru(i,a,b)    for(int i=a;i<b;i++)
#define  shuf(v)        shuffle(v.begin(),v.end(),RNG);
#define  time           cerr << "\nTime elapsed: " << clock() / (double) CLOCKS_PER_SEC << "s\n";

const double E = 1e-9, pi = 2 * acos(0);

struct Point {
    int x, y, id;
};

Point operator - (Point a, Point b){
    return (Point){a.x - b.x, a.y - b.y, -1};
}
long long cross(Point a, Point b){
    return 1ll * a.x * b.y - 1ll * a.y * b.x;
}
long long cross(Point a, Point b, Point c){
    return cross(b - a, c - a);
}

vector<Point> convex_hull(vector<Point> points){
    sort(points.begin(), points.end(), [&](Point a, Point b){
        if(a.y != b.y) return a.y < b.y;
        return a.x < b.x;
    });
    vector<Point> upper, lower;
    for(int i = 0; i < (int)points.size(); i++){
        while(upper.size() >= 2 && cross(upper.end()[-2], upper.end()[-1], points[i]) > 0)
            upper.pop_back();
        upper.push_back(points[i]);
    }
    for(int i = (int)points.size() - 1; i >= 0; i--){
        while(lower.size() >= 2 && cross(lower.end()[-2], lower.end()[-1], points[i]) > 0)
            lower.pop_back();
        lower.push_back(points[i]);
    }
    if(lower.size() > 2) upper.insert(upper.end(), lower.begin() + 1, lower.end() - 1);
    return upper;
}

int point_in_poly(const vector<Point> & poly, Point p){
    int many = 0;
    for(int i = 0; i < (int)poly.size(); i++){
        Point a = poly[i], b = poly[i + 1 < (int) poly.size() ? i + 1 : 0];
        if(a.x > b.x) swap(a, b);
        if(a.x <= p.x && p.x <= b.x){
            if(abs(a.x - b.x) == 0){
                if(min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y)) return -1;
            } else {
                double y = a.y + 1. * (b.y - a.y) / (b.x - a.x) * (p.x - a.x);
                if(abs(y - p.y) <= E) return -1;
                if(y >= p.y && p.x < b.x) many++;
            }
        }
    }
    return many % 2;
}

int32_t main(){
    flash;
    int t;cin>>t;
    while(t--){
        int n,q;cin>>n>>q;
        vector<int> vis(n,0);
        vector<Point> v(n);
        vector<vector<Point>> ans;

        for(int i=0;i<n;i++) cin>>v[i].x>>v[i].y , v[i].id=i;

        while(count(vis.begin(),vis.end(),0)>=3){
            vector<Point> it;
            for(int i=0;i<n;i++){
                if(vis[i]==0)
                    it.push_back(v[i]);
            }
            vector<Point> hull = convex_hull(it);

            for(auto ji:hull){
                Point ye = ji;
                vis[ye.id]=1;
            }
            ans.push_back(hull);
        }

        while(q--){
            int x,y;cin>>x>>y;
            int cur=0;
            for(vector<Point> it:ans)
                if(point_in_poly(it,{x,y})==1)
                    ++cur;
            cout << cur << endl;
        }

    }
    return 0;
}
