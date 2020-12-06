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

int n, m;
const int MAXN = 1e5 + 7;
const ll MOD = 1e9 + 7;
vector<int> g[MAXN];
int euler[2 * MAXN];
int sz[MAXN];
int tin[MAXN];
int tout[MAXN];
int id[MAXN];
int id_r[MAXN];
int timer = 0;
int par[MAXN];
int start[MAXN];
ll arr[MAXN];

int calc_size(int v, int p = -1) {
    sz[v] = 1;
    par[v] = max(p, 0);
    tin[v] = timer++;
    for (int u : g[v])
        if (u != p)
            sz[v] += calc_size(u, v);
    int mx = -1;
    for (int i = 0; i < SZ(g[v]); i++)
        if (mx == -1 || (g[v][i] != p && sz[g[v][i]] > sz[g[v][mx]]))
            mx = i;
    if (mx != -1)
        swap(g[v][mx], g[v][0]);
    tout[v] = timer++;
    return sz[v];
}

int pnt = 0;

void build_hld(int v, int p = -1, int start_v = -1) {
    if (start_v == -1)
        start_v = v;
    id[v] = pnt;
    euler[pnt++] = v;
    start[v] = start_v;
    if (!SZ(g[v])) {
        id_r[v] = pnt;
        return;
    }
    if (g[v][0] != p)
        build_hld(g[v][0], v, start_v);
    for (int u : g[v]) {
        if (g[v][0] == u || u == p)
            continue;
        build_hld(u, v, -1);
    }
    id_r[v] = pnt;
}

struct SegmentTree {
    struct Node {
        ll val = 0, add = 0;

        Node() = default;

        Node(ll x) {
            val = x;
        }

        Node(const Node &a, const Node &b) {
            val = a.val + b.val;
        }
    };

    Node *tree;
    int N = 1;

    SegmentTree() {}

    SegmentTree(int sz, int *a) {
        while (N < sz)
            N *= 2;
        tree = new Node[2 * N];
        for (int i = 0; i < sz; i++)
            tree[i + N] = Node(arr[a[i]]);
        for (int i = N - 1; i >= 0; i--)
            tree[i] = Node(tree[2 * i], tree[2 * i + 1]);
    }

    void push(int v, int tl, int tr) {
        if (!tree[v].add)
            return;
        tree[v].val += (tr - tl) * tree[v].add;
        if (v < N) {
            tree[2 * v].add += tree[v].add;
            tree[2 * v + 1].add += tree[v].add;
        }
        tree[v].add = 0;
    }

    ll get(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (r <= tl || tr <= l)
            return 0;
        if (l <= tl && tr <= r)
            return tree[v].val;
        int tm = (tl + tr) / 2;
        ll ret = (get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r)) % MOD;
        tree[v] = Node(tree[2 * v], tree[2 * v + 1]);
        return ret;
    }

    ll get(int v, int tl, int tr, int pos) {
        push(v, tl, tr);
        if (pos < tl || tr <= pos)
            return 0;
        if (tr - tl == 1)
            return tree[v].val;
        int tm = (tl + tr) / 2;
        ll ret = get(v * 2, tl, tm, pos) + get(v * 2 + 1, tm, tr, pos);
        tree[v] = Node(tree[2 * v], tree[2 * v + 1]);
        return ret;
    }

    ll get(int l, int r) {
        return get(1, 0, N, l, r);
    }

    ll get(int pos) {
        return get(1, 0, N, pos);
    }

    void push_seg(int v, int tl, int tr, int l, int r, ll x) {
        push(v, tl, tr);
        if (tr <= l || r <= tl)
            return;
        if (l <= tl && tr <= r) {
            tree[v].add += x;
            push(v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        push_seg(v * 2, tl, tm, l, r, x);
        push_seg(v * 2 + 1, tm, tr, l, r, x);
        tree[v] = Node(tree[2 * v], tree[2 * v + 1]);
    }

    void push_seg(int l, int r, ll x) {
        push_seg(1, 0, N, l, r, x);
    }
};

SegmentTree st;

ll sum_to_parent(int v) {
    if (v == 0)
        return 0;
    v = par[v];
    ll ans = 0;
    while (start[v] != 0) {
        ans = (ans + st.get(id[start[v]], id[v] + 1)) % MOD;
        v = par[start[v]];
    }
    return (ans + st.get(id[0], id[v] + 1)) % MOD;
}

ll sum_subtree(int v) {
    return st.get(id[v], id_r[v]);
}

void upd_to_parent(int v, ll x) {
    if (v == 0)
        return;
    v = par[v];
    while (start[v] != 0) {
        st.push_seg(id[start[v]], id[v] + 1, x);
        v = par[start[v]];
    }
    st.push_seg(id[0], id[v] + 1, x);
}

void upd_subtree(int v, ll x) {
    st.push_seg(id[v], id_r[v], x);
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        g[i].push_back(p);
        g[p].push_back(i);
    }
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    calc_size(0);
    build_hld(0);
    st = SegmentTree(pnt, euler);
    cout << st.get(id[n - 1]) << ' ';
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        ll sm = (sum_subtree(a) + sum_to_parent(a)) % MOD;
        upd_subtree(b, sm);
        upd_to_parent(b, sm);
        cout << st.get(id[n - 1]) << " \n"[i + 1 == m];
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
