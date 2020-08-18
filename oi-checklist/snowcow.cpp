#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;


#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
 
#define TMAX(type) numeric_limits<type>::max()
#define TMIN(type) numeric_limits<type>::min()
#ifdef LOCAL
#define ass(X) assert(X)
#else
#define ass(X) {}
#endif

const int MAXN = 1e5 + 7;

struct Fenwick{
	int tree[MAXN];
	Fenwick(){}

	void add(int pos, int what){
		// cout << pos << ' ' << what << '\n';
		if (pos < 0 || pos >= MAXN)
			return;
		for (int i = pos; i < MAXN; i |= (i + 1))
			tree[i] += what;
	}
	int get(int r){
		if (r < 0)
			return 0;
		int ans = 0;
		for (int i = r; i >= 0; i = (i & (i + 1)) - 1)
			ans += tree[i];
		return ans;
	}
	int get(int l, int r){
		if (r < l)
			return 0;
		return get(r) - get(l - 1);
	}
};

Fenwick a;
Fenwick b;

vector<int> g[MAXN];
map<int, int> have[MAXN];
int n, q;
int sz[MAXN];
int lft[MAXN], rgt[MAXN];
int timer = 0;
int dfs(int v, int p){
	sz[v] = 1;
	lft[v] = timer++;
	rgt[v] = lft[v];
	for (int u : g[v])
		if (u != p){
			sz[v] += dfs(u, v);
			rgt[v] = max(rgt[v], rgt[u]);
		}
	return sz[v];
}
void upd(int x, int y){
	a.add(lft[x], y);
	a.add(rgt[x] + 1, -y);
	b.add(lft[x], y * sz[x]);
}
int solve() {
    if (!(cin >> n >> q))
        return 1;
    timer = 0;
    for (int i = 1; i < n; i++){
    	int v, u;
    	cin >> v >> u;
    	--v, --u;
    	g[v].push_back(u);
    	g[u].push_back(v);
    }
    dfs(0, -1);
    for (int i = 0; i < q; i++){
    	int t;
    	cin >> t;
    	if (t == 1){
    		int x, c;
    		cin >> x >> c;
    		--x;
    		auto it = have[c].upper_bound(lft[x]);
    		if (it != have[c].begin() && rgt[prev(it)->second] >= rgt[x])
    			continue;
    		while (it != end(have[c]) && rgt[it->second] <= rgt[x]){
    			upd(it->second, -1);
    			have[c].erase(it++);
    		}
    		have[c][lft[x]] = x;
    		upd(x, 1);
    	}
    	else {
    		int v;
    		cin >> v;
    		--v;
    		// cout << a.get(lft[v]) << ' ' << b.get(lft[v] + 1, rgt[v]) << '\n';
    		cout << sz[v] * a.get(lft[v]) + b.get(lft[v] + 1, rgt[v]) << '\n';
    	}
    }
    return 0;
}
 
signed main() {
#ifndef LOCAL
    freopen("snowcow.in", "r", stdin);
    freopen("snowcow.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}