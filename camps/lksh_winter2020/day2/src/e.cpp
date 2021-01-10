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

struct Event {
    int type, v, time, distance, color;

    Event() {}

    Event(int type, int v, int time, int distance, int color) : type(type), v(v), time(time), distance(distance),
                                                                color(color) {}
};

struct SegmentTree {
    pair<int, int> *tree = nullptr;
    int N = 1;
    int real_sz = 0;

    SegmentTree() = default;

    explicit SegmentTree(int sz) {
        N = 1;
        real_sz = sz;
        while (N < sz)
            N *= 2;
        tree = new pair<int, int>[2 * N];
        fill(tree, tree + 2 * N, make_pair(-1, 0));
    }

    void upd(int v, int tl, int tr, int pos, pair<int, int> x) {
        if (pos < tl || tr <= pos)
            return;
        if (tr - tl == 1) {
            tree[v] = x;
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, pos, x);
        upd(v * 2 + 1, tm, tr, pos, x);
        tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    }

    inline void upd(int pos, pair<int, int> x) {
        upd(1, 0, N, pos, x);
    }

    pair<int, int> get(int v, int tl, int tr, int l, int r) {
        if (tr <= l || r <= tl)
            return {-1, 0};
        if (l <= tl && tr <= r)
            return tree[v];
        int tm = (tl + tr) / 2;
        return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
    }

    inline pair<int, int> get(int l, int r) {
        return get(1, 0, N, l, r);
    }

    inline pair<int, int> get_suffix(int l) {
        return get(1, 0, N, l, real_sz);
    }
};

int n;
const int MAXN = 1e5 + 7;
vector<pair<int, int>> g[MAXN];
vector<pair<int, int>> par[MAXN];
vector<int> to_compress[MAXN];
int sz[MAXN];
int used[MAXN];
Event events[MAXN];
SegmentTree sts[MAXN];


int calc_sz(int v, int p) {
    sz[v] = 1;
    for (auto[u, w] : g[v])
        if (u != p && !used[u])
            sz[v] += calc_sz(u, v);
    return sz[v];
}

void push_parent(int v, int p, int x, int d) {
    par[v].emplace_back(x, d);
    for (auto[u, w] : g[v]) {
        if (u != p && !used[u])
            push_parent(u, v, x, d + w);
    }
}

int find_centroid(int v, int p, int need) {
    for (auto[u, w] : g[v])
        if (sz[u] > need / 2 && u != p && !used[u])
            return find_centroid(u, v, need);
    return v;
}

void decomposition(int v) {
    calc_sz(v, -1);
    if (sz[v] == 1) {
        par[v].emplace_back(v, 0);
        return;
    }
    v = find_centroid(v, -1, sz[v]);
    used[v] = 1;
    push_parent(v, -1, v, 0);
    for (auto[u, w] : g[v])
        if (!used[u])
            decomposition(u);
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 1; i < n; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        g[v].emplace_back(u, w);
        g[u].emplace_back(v, w);
    }
    decomposition(0);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int type, v;
        cin >> type >> v;
        events[i].time = i;
        events[i].v = v - 1;
        events[i].type = type;
        if (type == 1) {
            int d, c;
            cin >> d >> c;
            events[i].color = c;
            events[i].distance = d;

            for (auto[u, dd] : par[v - 1]) {
                if (d - dd >= 0)
                    to_compress[u].push_back(d - dd);
            }
        }
    }
//    for (int i = 0; i < n; i++) {
//        cout << i + 1 << ": \n\t";
//        for (auto[v, d] : par[i])
//            cout << "{" << v + 1 << ", " << d << "} ";
//        cout << '\n';
//    }
    for (int i = 0; i < n; i++) {
        sort(ALL(to_compress[i]));
        to_compress[i].resize(unique(ALL(to_compress[i])) - to_compress[i].begin());
        sts[i] = SegmentTree(SZ(to_compress[i]));
//        cout << i + 1 << ": ";
//        for (int x : to_compress[i])
//            cout << x << ' ';
//        cout << '\n';
    }
    for (int i = 0; i < q; i++) {
        auto &e = events[i];
//        cerr << e.type << ' ' << e.v << '\n';
        if (e.type == 1) {
            for (auto[u, dd] : par[e.v])
                if (e.distance - dd >= 0) {
                    int dist = e.distance - dd;
                    int index = (int) (lower_bound(ALL(to_compress[u]), dist) - to_compress[u].begin());
//                    cout << dist << ' ' << index << ' ' << e.v + 1 << ' ' << u + 1 << '\n';
                    sts[u].upd(index, make_pair(e.time, e.color));
                }
        } else {
            pair<int, int> mx = {-1, 0};
            for (auto[u, dd] : par[e.v]) {
                int index = (int) (lower_bound(ALL(to_compress[u]), dd) - to_compress[u].begin());
                auto t = sts[u].get_suffix(index);
//                cout << index << ' ' << dd << ' ' << t.first << ' ' << t.second << '\n';
                mx = max(mx, sts[u].get_suffix(index));
            }
            cout << mx.second << '\n';
        }
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
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
