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
struct Node {
    int val = 0; // sum w * sz
    int sum = 0; // sum w
    int push = 0;
};
const int MAXN = 2e5 + 7;
int sz[MAXN];
int start[MAXN];
int tin[MAXN];
int tout[MAXN];
Node tree_plus[4 * MAXN];
//Node tree_minus[4 * MAXN];
int id[MAXN];
int arr[MAXN];
int par[MAXN];
vector<int> g[MAXN];
int N;
int timer = 0;

int calc_sz(int v, int p = -1) {
    par[v] = max(0, p);
    sz[v] = 1;
    tin[v] = timer++;
    for (int u : g[v])
        if (u != p)
            sz[v] += calc_sz(u, v);
    int mx = -1;
    for (int i = 0; i < SZ(g[v]); i++)
        if (g[v][i] != p && (mx == -1 || sz[g[v][i]] > sz[g[v][mx]]))
            mx = i;
    if (mx != -1)
        swap(g[v][0], g[v][mx]);
    tout[v] = timer++;
    return sz[v];
}

int pnt = 0;

void build_hld(int v, int p = -1, int start_v = -1) {
    if (start_v == -1)
        start_v = v;
    start[v] = start_v;
    id[v] = pnt;
    tree_plus[pnt + N].sum = arr[v];
    tree_plus[pnt + N].val = tree_plus[pnt + N].push = 0;
    if (v != 0)
        tree_plus[pnt + N].sum -= arr[par[v]];
    pnt++;
    if (!SZ(g[v]))
        return;
    if (g[v][0] != p)
        build_hld(g[v][0], v, start_v);
    for (int u : g[v])
        if (u != p && g[v][0] != u)
            build_hld(u, v, -1);
}

bool is_anc(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

void push(Node *tree, int v) {
    if (tree[v].push == 0)
        return;
    tree[v].val += tree[v].push * tree[v].sum;
    if (v < N) {
        tree[2 * v].push += tree[v].push;
        tree[2 * v + 1].push += tree[v].push;
    }
    tree[v].push = 0;
}

void pull(Node *tree, int v) {
    tree[v].sum = tree[2 * v].sum + tree[2 * v + 1].sum;
    tree[v].val = tree[2 * v].val + tree[2 * v + 1].val;
}

int get(Node *tree, int v, int tl, int tr, int l, int r) {
    push(tree, v);
    if (r <= tl || tr <= l)
        return 0;
    if (l <= tl && tr <= r)
        return tree[v].val;
    int tm = (tl + tr) / 2;
    int ret = get(tree, v * 2, tl, tm, l, r) + get(tree, v * 2 + 1, tm, tr, l, r);
    pull(tree, v);
    return ret;
}

void upd(Node *tree, int v, int tl, int tr, int l, int r, int x) {
    push(tree, v);
    if (r <= tl || tr <= l)
        return;
    if (l <= tl && tr <= r) {
        tree[v].push = x;
        push(tree, v);
        return;
    }
    int tm = (tl + tr) / 2;
    upd(tree, v * 2, tl, tm, l, r, x);
    upd(tree, v * 2 + 1, tm, tr, l, r, x);
    pull(tree, v);
}

int get_ans(int a, int b) {
    int ans = 0;
    for (int i = 0; i < 2; i++) {
        while (!is_anc(start[a], b)) {
            ans += get(tree_plus, 1, 0, N, id[start[a]], id[a] + 1) /*- get(tree_minus, 1, 0, N, id[start[a]], id[a] + 1)*/;
            a = par[start[a]];
        }
        swap(a, b);
    }
    if (id[a] > id[b])
        swap(a, b);
    return ans + get(tree_plus, 1, 0, N, id[a], id[b] + 1) /*- get(tree_minus, 1, 0, N, id[a], id[b] + 1)*/;
}

void update_path(int a, int b, int x) {
    for (int i = 0; i < 2; i++) {
        while (!is_anc(start[a], b)) {
            upd(tree_plus, 1, 0, N, id[start[a]], id[a] + 1, x);
//            upd(tree_minus, 1, 0, N, id[start[a]], id[a] + 1, x);
            a = par[start[a]];
        }
        swap(a, b);
    }
    if (id[a] > id[b])
        swap(a, b);
    upd(tree_plus, 1, 0, N, id[a], id[b] + 1, x);
//    upd(tree_minus, 1, 0, N, id[a], id[b] + 1, x);
}

int solve() {
    if (!(cin >> n))
        return 1;
    N = 1;
    while (N < n)
        N *= 2;
    timer = 0, pnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
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
    for (int i = n; i < N; i++) {
        /*tree_minus[i].push =*/ tree_plus[i].push = 0;
        /*tree_minus[i].val =*/ tree_plus[i].val = 0;
        /*tree_minus[i].sum =*/ tree_plus[i].sum = 0;
    }
    for (int i = N - 1; i >= 0; i--) {
        pull(tree_plus, i);
//        pull(tree_minus, i);
        tree_plus[i].push = 0;
//        tree_minus[i].push = 0;
    }
    update_path(0, 0, 1);
    for (int i = 1; i < n; i++) {
        cout << get_ans(0, i) << '\n';
        update_path(0, i, 1);
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
