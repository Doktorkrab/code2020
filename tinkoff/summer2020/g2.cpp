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
 
const int MAXN = 2e5 + 7;
int n, m, max_c, q;
struct Edge{
    int from, to, cost;
    bool operator< (const Edge& oth) const {
        return tie(cost, from, to) < tie(oth.cost, oth.from, oth.to);
    }
};

vector<pair<int, int>> g[MAXN];
vector<int> queries[MAXN];
int color[MAXN];
int p[MAXN], sz[MAXN];
int par[MAXN];
int p_ind[MAXN];
Edge edges[MAXN];

int find_set(int v){
    if (p[v] == v)
        return v;
    return p[v] = find_set(p[v]);
}

bool un(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if (a == b)
        return false;
    if (sz[a] > sz[b])
        swap(a, b);
    p[a] = b;
    sz[b] += sz[a];
    return true;
}

void build_mst(){
    sort(edges, edges + m);
    for (int i = 0; i < n; i++){
        p[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < m; i++){
        auto [v, u, c] = edges[i];
        if (un(v, u)){
            //cout << v + 1 << "<=>" << u + 1 << ' ' << c << '\n';
            g[v].push_back({u, c});
            g[u].push_back({v, c});
        }
    }
}

void dfs(int v, int pp = -1){
    par[v] = pp;
    for (auto [u, d] : g[v])
        if (u != pp)
            dfs(u, v);
}

struct Node{
    int mx, mn;
};

struct SegmentTree{
    vector<Node> st;
    int N;
    SegmentTree() : st(0), N(0) {}
    Node recalc(const Node& a, const Node& b){
        return {max(a.mx, b.mx), min(a.mn, b.mn)};
    }
    SegmentTree(const vector<pair<int, int>>& arr){
        N = 1;
        while (N < SZ(arr))
            N *= 2;
        st.resize(2 * N + 1, {TMAX(int), TMAX(int)});

        for (int i = 0; i < SZ(arr); i++)
            st[i + N] = {arr[i].first, arr[i].first};

        for (int i = N - 1; i >= 0; i--)
            st[i] = recalc(st[2 * i], st[2 * i + 1]);
    }

    void update(int v, int tl, int tr, int pos, int x){
        if (pos < tl || tr <= pos)
            return;
        if (tr - tl == 1){
            st[v] = {x, x};
            return;
        }
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, pos, x);
        update(v * 2 + 1, tm, tr, pos, x);
        st[v] = recalc(st[2 * v], st[2 * v + 1]);
    }

    int get_le(int v, int tl, int tr, int x){
        //cout << v << ' ' << tl << ' ' << tr << ' ' << st[v].mn << ' ' << st[v].mx << ' ' << x << "!\n";
        if (st[v].mn >= x)
            return TMAX(int);
        if (tr - tl == 1)
            return tl;
        int tm = (tl + tr) / 2;
        if (st[2 * v].mn < x)
            return get_le(2 * v, tl, tm, x);
        if (st[2 * v + 1].mn < x)
            return get_le(2 * v + 1, tm, tr, x);
        return TMAX(int);
    }

    int get_ge(int v, int tl, int tr, int x){
        //cout << v << ' ' << tl << ' ' << tr << ' ' << st[v].mn << ' ' << st[v].mx << ' ' << x << "?\n";
        if (st[v].mx <= x)
            return TMAX(int);
        if(tr - tl == 1)
            return tl;
        int tm = (tl + tr) / 2;
        if (st[2 * v].mx > x)
            return get_ge(2 * v, tl, tm, x);
        if (st[2 * v + 1].mx > x)
            return get_ge(2 * v + 1, tm, tr, x);
        return TMAX(int);
    }
    int get_le(int x){
        return get_le(1, 0, N, x);
    }
    int get_ge(int x){
        return get_ge(1, 0, N, x);
    }
    
    void update(int pos, int x){
        update(1, 0, N, pos, x);
    }
};

SegmentTree segs[MAXN];
SegmentTree ans;
int get_ans(int x){
    int a = segs[x].get_ge(color[x]);
    int b = segs[x].get_le(color[x]);
    //cout << a << ' ' << b << '\n';
    if (a > b)
        swap(a, b);
    if (SZ(g[x]) <= a)
        return TMAX(int);
    else
        return g[x][a].second;
}
int solve() {
    if (!(cin >> n >> m >> max_c >> q))
        return 1;
    for (int i = 0; i < m; i++){
        int v, u, c;
        cin >> v >> u >> c;
        --v, --u;
        edges[i] = {v, u, c}; 
    }
    build_mst();
    dfs(0);
    for (int i = 0; i < n; i++)
        cin >> color[i];
    ans = SegmentTree(vector<pair<int, int>>(n, make_pair(TMAX(int), TMAX(int))));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < SZ(g[i]); j++)
            if (g[i][j].first == par[i]){
                swap(g[i][j], g[i].back());
                g[i].pop_back();
                break;
            }
        sort(ALL(g[i]), [&](const pair<int, int>& a, const pair<int, int>& b){ return tie(a.second, a.first) < tie(b.second, a.first); });
        for (int j = 0; j < SZ(g[i]); j++){
            if (par[g[i][j].first] == i)
                p_ind[g[i][j].first] = j;
            g[i][j].first = color[g[i][j].first];
        }
        segs[i] = SegmentTree(g[i]);
        ans.update(i, get_ans(i));
    }
    //cerr << "ok\n";
    for (int i = 0; i < q; i++){
        int v, x;
        cin >> v >> x;
        --v;
        color[v] = x;
        ans.update(v, get_ans(v));
        if (par[v] >= 0){
            //cerr << '\t' << i << '\n';
            segs[par[v]].update(p_ind[v], color[v]);
            ans.update(par[v], get_ans(par[v]));
        }
        //for (int j = 0; j < n; j++)
            //cout << get_ans(j) << " \n"[j + 1 == n];
        cout << ans.st[1].mn << '\n';
        //cerr << i + 1 << '\n';
    }

    return 0;
}
 
signed main() {
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
