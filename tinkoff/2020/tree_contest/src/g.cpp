#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
#define int ll

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
    int t, x, index;

    bool operator<(const Event &rhs) const {
        return std::tie(t, x, index) < std::tie(rhs.t, rhs.x, rhs.index);
    }
};

int n, m;
const int MAXN = 2e5 + 7;
vector<pair<int, int>> g[MAXN];
int used[MAXN];
int sz[MAXN];
vector<pair<int, int>> parents[MAXN];
vector<pair<int, int>> events[MAXN];
Event global_events[MAXN];
unordered_map<int, int> indexes[MAXN];
int start[MAXN];

struct SegmentTree {
    int *nodes;
    int N;

    explicit SegmentTree(int x) {
        N = 1;
        while (N < x)
            N *= 2;
        nodes = new int[2 * N];
        fill(nodes, nodes + 2 * N, 0);
    }

    SegmentTree() = default;

    void insert(int v, int tl, int tr, int pos, int x) {
        if (pos < tl || tr <= pos)
            return;
        if (tr - tl == 1) {
            nodes[v] = x;
            return;
        }
        int tm = (tl + tr) / 2;
        insert(v * 2, tl, tm, pos, x);
        insert(v * 2 + 1, tm, tr, pos, x);
        nodes[v] = max(nodes[2 * v], nodes[2 * v + 1]);
    }

    void insert(int pos, int x) {
        insert(1, 0, N, pos, x);
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (r <= tl || tr <= l)
            return 0;
        assert(v < 2 * N);
        if (l <= tl && tr <= r) {
//            cerr << nodes[v] << '\n';
            return nodes[v];
        }
        int tm = (tl + tr) / 2;
        return max(get(v * 2, tl, tm, l, r),
                   get(v * 2 + 1, tm, tr, l, r));
    }

    int get(int l, int r) {
        return get(1, 0, N, l, r);
    }
};

SegmentTree st;

int calc_sz(int v, int p = -1) {
    sz[v] = 1;
    for (auto[u, w] : g[v])
        if (u != p && !used[u])
            sz[v] += calc_sz(u, v);
    return sz[v];
}

int find_centroid(int v, int p, int need) {
    for (auto[u, w] : g[v])
        if (u != p && !used[u] && sz[v] > need / 2)
            return find_centroid(u, v, need);
    return v;
}

void push_parent(int v, int p, int dist, int x) {
    parents[v].emplace_back(x, dist);
    for (auto[u, w] : g[v])
        if (u != p && !used[u])
            push_parent(u, v, dist + w, x);
}

void decomposition(int v) {
    calc_sz(v);

    v = find_centroid(v, -1, sz[v]);
    push_parent(v, -1, 0, v);
    used[v] = 1;
    for (auto[u, w] : g[v])
        if (!used[u])
            decomposition(u);
}


int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        g[i].clear(), parents[i].clear(), events[i].clear();

    for (int i = 0; i < n - 1; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        g[v].emplace_back(u, w);
        g[u].emplace_back(v, w);
    }
    decomposition(0);
    for (int i = 0; i < n; i++) {
        sort(ALL(parents[i]), [&](const pair<int, int> &a, const pair<int, int> &b) {
            return make_pair(a.second, a.first) < make_pair(b.second, b.first);
        });
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        int x, t;
        cin >> x >> t;
        for (auto[v, w] : parents[x - 1]) {
            events[v].emplace_back(w + t, i);
        }
        indexes[i].clear();
        global_events[i] = {t, x - 1, i};
    }
    int st_sz = 0;
    for (int i = 0; i < n; i++) {
        sort(ALL(events[i]));
        for (int j = 0; j < SZ(events[i]); j++)
            indexes[events[i][j].second][i] = j;
        st_sz += SZ(events[i]);
    }
    st = SegmentTree(st_sz);
    st_sz = 0;
    for (int i = 0; i < n; i++) {
        start[i] = st_sz;
        st_sz += SZ(events[i]);
    }
    sort(global_events, global_events + m);
    for (int i = 0; i < m; i++) {
        int now = 1;
        auto[t, v, index] = global_events[i];
        for (auto[u, w] : parents[v]) {
            int cnt = (lower_bound(ALL(events[u]), make_pair(t - w + 1, 0LL)) - events[u].begin());
            now = max(now, st.get(start[u], start[u] + cnt) + 1);
//            cout << v + 1 << ' ' << u + 1 << " " << now << ' ' << st.get(start[u], start[u] + cnt) + 1 << '\n';
        }
        for (auto[u, w] : parents[v])
            st.insert(start[u] + indexes[index][u], now);
    }
    cout << st.get(0, st.N) << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("g.in", "r", stdin);
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
