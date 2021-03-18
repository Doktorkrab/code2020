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
 
int n, gold;
const int MAXN = 1e5 + 7;
const int MOD = 1e9 + 7;
const int MAXLOG = 18;
struct Edge{
    int u, w, t;
};
vector<Edge> g[MAXN];
vector<int> g1[MAXN];
Edge edges[2 * MAXN];
map<pair<int, int>, int> indexes;
int sum[MAXN];
int sumt[MAXN];
int par[MAXLOG][MAXN];
int tin[MAXN], tout[MAXN];
int timer;

void dfs(int v, int p){
    par[0][v] = p;
    tin[v] = timer++;
    for (int i = 1; i < MAXLOG; i++)
        par[i][v] = par[i - 1][par[i - 1][v]];
    for (auto [u, w, t] : g[v]){
        if (u == p)
            continue;
        sum[u] = (sum[v] + w) % MOD;
        sumt[u] = (sumt[v] + t) % MOD;
        dfs(u, v);
    }
    tout[v] = timer++;
}

bool is_ancestor(int a, int b){
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b){
    if (is_ancestor(a, b))
        return a;
    for (int i = MAXLOG - 1; i >= 0; i--){
        int v = par[i][a];
        if (!is_ancestor(v, b))
            a = v;
    }
    return par[0][a];
}
int add(int a, int b){

    return ((1LL * a + b) % MOD + MOD) % MOD;
}
void solvet0(){
    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        int v, x, y;
        cin >> v >> x >> y;
        assert(v == 1);
        --x, --y;
        cout << 1LL * gold * add(add(sum[x], sum[y]), -2 * sum[lca(x, y)]) % MOD << '\n';
    }
}

vector<Edge> st;
int dfs1(int v, int p, int end){
    if (v == end){
        int tnow = gold;
        for (auto e : st)
            tnow = (tnow + e.t) % MOD;
        int ans = 0;
        for (auto e : st){
            tnow = ((tnow - e.t) % MOD + MOD) % MOD;
            int now = 1LL * tnow * e.w % MOD;
            ans = (ans + now) % MOD;
        }
        return ans;
    }
    for (int i : g1[v]){
        auto e = edges[i];
        if (e.u == p)
            continue;
        st.push_back(e);
        int ans = dfs1(e.u, v, end);
        st.pop_back();
        if (ans != -1)
            return ans;
    }
    return -1;
}

void solven2(){
    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        int v, x, y, t;
        cin >> v >> x >> y;
        --x, --y;
        if (v == 0){
            cin >> t;
            if (x > y)
                swap(x, y);
            int ind = indexes[{x, y}];
            edges[ind].t = t;
            edges[ind ^ 1].t = t;
            continue;
        }
        cout << dfs1(x, -1, y) << '\n';
    }
}
int get(int len){
    return (1LL * len * (len - 1) / 2) % MOD;
}
void solveteq(int teq){
    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        int v, x, y;
        cin >> v >> x >> y;
        assert(v == 1);
        --x, --y;
        int len = add(add(sum[x], sum[y]), -(2 * sum[lca(x, y)] % MOD));
        cout << add(1LL * gold * len % MOD, 1LL * get(len) * teq % MOD) << '\n';
    }
}

int solve() {
    if (!(cin >> n >> gold))
        return 1;
    timer = 0;
    for (int i = 0; i < n; i++)
        g[i].clear(), g1[i].clear();
    bool allt0 = true;
    int teq = -1;
    bool d1 = true;
    bool allteq = true;
    for (int i = 0; i + 1 < n; i++){
        int v, u, d, t;
        cin >> v >> u >> d >> t;
        --v, --u;
        if (v > u)
            swap(v, u);
        indexes[{v, u}] = 2 * i;
        allt0 &= (t == 0);
        d1 &= (d == 1);
        if (teq == -1)
            teq = t;
        allteq &= (teq == t);
        edges[2 * i] = {u, d, t};
        edges[2 * i + 1] = {v, d, t};
        g[v].push_back({u, d, t});
        g[u].push_back({v, d, t});
        g1[v].push_back(2 * i);
        g1[u].push_back(2 * i + 1);
    }
    dfs(0, 0);
    if (allt0)
        solvet0();
    else if (d1 && allteq)
        solveteq(teq);
    else
        solven2();

    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
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
