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

int n;
const int MAXN = 2e5 + 7;
int sz[MAXN];
int start[MAXN];
vector<int> g[MAXN]; // no parent
int id[MAXN], pnt = 0;
int tin[MAXN], tout[MAXN], timer = 0;
int par[MAXN];
int weights[MAXN];
int euler_plus[MAXN];
int euler_minus[MAXN];

int calc_sz(int v) {
    tin[v] = timer++;
    for (int u : g[v]) {
        par[u] = v;
        sz[v] += calc_sz(u);
    }
    tout[v] = timer++;
    for (int i = 0; i < SZ(g[v]); i++)
        if (sz[g[v][i]] > sz[g[v][0]])
            swap(g[v][i], g[v][0]);
    return sz[v];
}

void build_hld(int v, int start_v = -1) {
    euler_plus[pnt] = weights[v];
    if (v != 0)
        euler_minus[pnt] = weights[par[v]];
    id[v] = pnt++;
    if (start_v == -1)
        start_v = v;
    start[v] = start_v;
    if (!SZ(g[v]))
        return;
    build_hld(g[v][0], start_v);
    for (int i = 1; i < SZ(g[v]); i++)
        build_hld(g[v][i], -1);
}

struct SegmentTree {
    struct Node {
        ll val = 0; // \sum (w * sz)
        ll sum = 0; // \sum w
        ll push = 0;

        Node() = default;

        explicit Node(int s) : sum(s) {}

        Node(const Node &a, const Node &b) {
            val = a.val + b.val;
            sum = a.sum + b.sum;
        }
    };

    Node tree[4 * MAXN];
    int N = 1;

    SegmentTree() = default;

    SegmentTree(int sz, int *arr) {
        while (N < sz)
            N *= 2;
        fill(tree, tree + 2 * N, Node());
        for (int i = 0; i < sz; i++)
            tree[i + N] = Node(arr[i]);
        for (int i = N - 1; i >= 0; i--)
            tree[i] = Node(tree[2 * i], tree[2 * i + 1]);
    }

    void push(int v) {
        if (tree[v].push == 0)
            return;
        tree[v].val += tree[v].push * tree[v].sum;
        if (v < N) {
            tree[2 * v].push += tree[v].push;
            tree[2 * v + 1].push += tree[v].push;
        }
        tree[v].push = 0;
    }

    ll get(int v, int tl, int tr, int l, int r) {
        push(v);
        if (r <= tl || tr <= l)
            return 0;
        if (l <= tl && tr <= r)
            return tree[v].val;
        int tm = (tl + tr) / 2;
        int ret = get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r);
        tree[v] = Node(tree[2 * v], tree[2 * v + 1]);
        return ret;
    }

    ll get(int l, int r) {
        return get(1, 0, N, l, r);
    }

    void push_seg(int v, int tl, int tr, int l, int r, int x) {
        push(v);
        if (tr <= l || r <= tl)
            return;
        if (l <= tl && tr <= r) {
            tree[v].push += x;
            push(v);
            return;
        }
        int tm = (tl + tr) / 2;
        push_seg(v * 2, tl, tm, l, r, x);
        push_seg(v * 2 + 1, tm, tr, l, r, x);
        tree[v] = Node(tree[2 * v], tree[2 * v + 1]);
    }

    void push_seg(int l, int r, int x) {
        push_seg(1, 0, N, l, r, x);
    }
    void set(int sz, int *arr){
        N = 1;
        while (N < sz)
            N *= 2;
        fill(tree, tree + 2 * N, Node());
        for (int i = 0; i < sz; i++)
            tree[i + N] = Node(arr[i]);
        for (int i = N - 1; i >= 0; i--)
            tree[i] = Node(tree[2 * i], tree[2 * i + 1]);
    }
};

SegmentTree plus_st, minus_st;

inline bool is_anc(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

void update(int a) {
    while (!is_anc(start[a], 0)) {
        plus_st.push_seg(id[start[a]], id[a] + 1, 1);
        minus_st.push_seg(id[start[a]], id[a] + 1, 1);
        a = par[start[a]];
    }
    plus_st.push_seg(id[0], id[a] + 1, 1);
    minus_st.push_seg(id[0], id[a] + 1, 1);
}

int get(int a) {
    int ans_p = 0, ans_m = 0;
    while (!is_anc(start[a], 0)) {
        ans_p += plus_st.get(id[start[a]], id[a] + 1);
        ans_m += minus_st.get(id[start[a]], id[a] + 1);
        a = par[start[a]];
    }
    ans_p += plus_st.get(id[0], id[a] + 1);
    ans_m += minus_st.get(id[0], id[a] + 1);
    return ans_p - ans_m;
}

int solve() {
    if (!(cin >> n))
        return 1;
    timer = 0, pnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
        g[i].clear();
        g[i].shrink_to_fit();
    }
    int p;
    for (int i = 1; i < n; i++) {
        cin >> p;
        g[p - 1].push_back(i);
    }
    par[0] = 0;
    calc_sz(0);
    build_hld(0);
    plus_st.set(n, euler_plus);
    minus_st.set(n, euler_minus);
    update(0);
    for (int i = 1; i < n; i++) {
        cout << get(i) << '\n';
        update(i);
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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