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

const int MAXN = 3e5 + 7;

struct SegmentTree {
    struct Node {
        int push = -1;
        int val = MAXN;
    };
    Node tree[4 * 3 * MAXN];
    int N = 1;

    SegmentTree() = default;

    explicit SegmentTree(int n) {
        while (N < n)
            N *= 2;
    }

    void push(int v, int tl, int tr) {
        if (tree[v].push == -1)
            return;
        if (v < N) {
            tree[2 * v].val = tree[2 * v + 1].val = tree[v].push;
            tree[2 * v].push = tree[2 * v + 1].push = tree[v].push;
        }
        tree[v].push = -1;
    }

    void pull(int v) {
        tree[v].val = max(tree[2 * v].val, tree[2 * v + 1].val);
    }

    void push_seg(int v, int tl, int tr, int l, int r, int x) {
//        cout << "!" << tl << ' ' << tr << ' ' << l << ' ' << r << '\n';
        if (tr <= l || r <= tl)
            return;
        if (l <= tl && tr <= r) {
//            cout << tl << ' ' << tr << '\n';
            tree[v].val = tree[v].push = x;
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        push_seg(v * 2, tl, tm, l, r, x);
        push_seg(v * 2 + 1, tm, tr, l, r, x);
        pull(v);
    }

    void push_seg(int l, int r, int x) {
        push_seg(1, 0, N, l, r, x);
    }

    int get(int v, int tl, int tr, int pos) {
        if (pos < tl || tr <= pos)
            return MAXN;
//        cout << v << ' ' << tl << ' ' << tr << ' ' << pos << '\n';
//        cout << '\t' << tree[v].val << ' ' << tree[v].push << '\n';
        if (tr - tl == 1)
            return tree[v].val;
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        int ret = min(get(v * 2, tl, tm, pos), get(v * 2 + 1, tm, tr, pos));
        pull(v);
        return ret;
    }

    int get(int pos) {
        return get(1, 0, N, pos);
    }
};

const int OPEN = -1, CLOSE = 1, BALL = 0;

struct Event {
    int type, x, index;

    bool operator<(const Event &oth) const {
        return tie(x, type) < tie(oth.x, oth.type);
    }
};

struct Rect {
    int a, b, c, d;
};
Event events[3 * MAXN];
unordered_set<int> have[MAXN];
vector<int> g[MAXN];
Rect borders[MAXN];
Rect points[MAXN];
int par[MAXN];
int ans[MAXN];
bool used[MAXN];
int n, m;

void dfs(int v, unordered_set<int> &now) {
    now = have[v];
    used[v] = true;
    for (int u : g[v]) {
        unordered_set<int> ret;
        dfs(u, ret);
        if (SZ(ret) > SZ(now))
            swap(now, ret);
        for (int x : ret)
            now.insert(x);
    }
    ans[v] = SZ(now);
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    int pnt = 0;
    vector<int> to_sort(2 * n + m);
    for (int i = 0; i < n; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
//        cerr << 2 * i << ' ' << SZ(to_sort) << '\n';
        to_sort[2 * i] = b;
        to_sort[2 * i + 1] = d + 1;
        borders[i] = {a, b, c, d + 1};
        par[i] = MAXN;
    }
    for (int i = 0; i < m; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        points[i] = {x, y, c, 0};
        to_sort[2 * n + i] = y;
    }
    sort(ALL(to_sort));
    to_sort.erase(unique(ALL(to_sort)), to_sort.end());
    for (int i = 0; i < n; i++) {
        borders[i].b = lower_bound(ALL(to_sort), borders[i].b) - to_sort.begin();
        borders[i].d = lower_bound(ALL(to_sort), borders[i].d) - to_sort.begin();
        events[pnt++] = {OPEN, borders[i].a, i};
        events[pnt++] = {CLOSE, borders[i].c, i};
    }
    for (int i = 0; i < m; i++) {
        points[i].b = lower_bound(ALL(to_sort), points[i].b) - to_sort.begin();
        events[pnt++] = {BALL, points[i].a, i};
    }
    int k = SZ(to_sort);
    SegmentTree seg(k);
    sort(events, events + pnt);

    for (int i = 0; i < pnt; i++) {
        auto[type, _, ind] = events[i];
        if (type == BALL) {
            int p = seg.get(points[ind].b);
//            cout << points[ind].a << ' ' << to_sort[points[ind].b] << ' ' << p << '\n';
            if (p > n)
                continue;
            have[p].insert(points[ind].c);
        }
        if (type == OPEN) {
            int p = seg.get(borders[ind].b);
            par[ind] = p;
            if (p < n) {
                g[p].push_back(ind);
//                cout << p + 1 << "->" << ind + 1 << '\n';
            }
            seg.push_seg(borders[ind].b, borders[ind].d, ind);
        }
        if (type == CLOSE)
            seg.push_seg(borders[ind].b, borders[ind].d, par[ind]);
    }
    for (int i = 0; i < n; i++)
        if (!used[i]) {
            unordered_set<int> ret;
            dfs(i, ret);
        }
    for (int i = 0; i < n; i++)
        cout << ans[i] << '\n';
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
