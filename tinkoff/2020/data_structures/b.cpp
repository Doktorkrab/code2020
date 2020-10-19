#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ostream>

using namespace std;
using ll = long long;

using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

mt19937 rnd(239);

struct Node {
    pair<int, int> x = {0, 0};
    int y = 0;
    int left = 0;
    int right = 0;
    int sz = 0;

    Node() = default;

    explicit Node(const pair<int, int> &_x) : x(_x), y(rnd()), sz(1) {}
};

const int MAXC = 1e5;
Node nodes[MAXC];
int pnt = 1;

int new_node(const pair<int, int> &x) {
    nodes[pnt] = Node(x);
    return pnt++;
}

int safe_sz(int x) {
    return (x ? nodes[x].sz : 0);
}

int recalc(int x) {
    nodes[x].sz = safe_sz(nodes[x].left) + 1 + safe_sz(nodes[x].right);
    return x;
}

pair<int, int> split(int a, const pair<int, int> &x) {
    if (!a)
        return {0, 0};
    if (nodes[a].x <= x) {
        auto ret = split(nodes[a].right, x);
        nodes[a].right = ret.first;
        return {recalc(a), ret.second};
    }
    auto ret = split(nodes[a].left, x);
    nodes[a].left = ret.second;
    return {ret.first, recalc(a)};
}

int insert(int a, int x) {
    if (!a)
        return x;
    if (nodes[a].y > nodes[x].y) {
        auto t = split(a, nodes[x].x);
        nodes[x].left = t.first;
        nodes[x].right = t.second;
        return recalc(x);
    }
    if (nodes[a].x < nodes[x].x) {
        nodes[a].right = insert(nodes[a].right, x);
        return recalc(a);
    }
    nodes[a].left = insert(nodes[a].left, x);
    return recalc(a);
}

int gt(int a, const pair<int, int> &x) {
    if (!a)
        return a;
    if (nodes[a].x > x)
        return gt(nodes[a].left, x) + 1 + safe_sz(nodes[a].right);
    return gt(nodes[a].right, x);
}

const int MAXN = 5e4 + 7;

struct SegmentTree {
    struct SegNode {
        ordered_set<pair<int, int>> have;
    };
    SegNode tree[4 * MAXN];
    int N;

    explicit SegmentTree(int n) {
        N = 1;
        while (N <= n)
            N *= 2;
    }

    void update(int pos, int what) {
        int v = pos + N;
        int was = tree[v].have.begin()->first;
        while (v > 1) {
            tree[v].have.erase({was, pos});
            tree[v].have.insert({2 * what, pos});
            v >>= 1;
        }
    }

    int get_gt(int v, int tl, int tr, int l, int r, int x) {
        if (tr <= l || r <= tl)
            return 0;
        if (l <= tl && tr <= r) {
//            cout << v << ' ' << x << ' ' << SZ(tree[v].have) - tree[v].have.order_of_key({x + 1, -1}) << '\n';
//            for (auto [a, b] : tree[v].have)
//                cout << "(" << a << " " << b + 1 << "), ";
//            cout << '\n';
            return SZ(tree[v].have) - tree[v].have.order_of_key({x + 1, -1});  // v > x
        }
        int tm = (tl + tr) / 2;
        return get_gt(v * 2, tl, tm, l, r, x) + get_gt(v * 2 + 1, tm, tr, l, r, x);
    }

    int get_gt(int l, int r, int x) {
        return get_gt(1, 0, N, l, r, x);
    }

    int get_le(int v, int tl, int tr, int l, int r, int x) {
        if (tr <= l || r <= tl)
            return 0;
        if (l <= tl && tr <= r) {
//            cout << "!" << v << ' ' << x << ' ' << tree[v].have.order_of_key({x, -1}) << '\n';
//            for (auto [a, b] : tree[v].have)
//                cout << "(" << a << " " << b + 1 << "), ";
//            cout << '\n';
            return tree[v].have.order_of_key({x, -1});  // v < x
        }
        int tm = (tl + tr) / 2;
        return get_le(v * 2, tl, tm, l, r, x) + get_le(v * 2 + 1, tm, tr, l, r, x);
    }

    int get_le(int l, int r, int x) {
        return get_le(1, 0, N, l, r, x);
    }
};

int n;
int arr[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    SegmentTree seg(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        seg.update(i, x);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        char type;
        cin >> type;
        if (type == 'C') {
            int pos, x;
            cin >> pos >> x;
            seg.update(pos - 1, x);
        }
        if (type == 'Q') {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--;
            int ans1 = seg.get_gt(x1, x2, (y1 + y2));
            int ans2 = seg.get_le(x1, x2, (y1 + y2));
//            cout << ans1 << ' ' << ans2 << '\n';
            if (ans1 == ans2)
                cout << "0\n";
            else if (ans1 > ans2)
                cout << "2\n";
            else
                cout << "1\n";
        }
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
