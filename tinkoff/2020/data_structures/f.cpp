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

int n, k;
const int MAXN = 1e5 + 7;

struct SegmentTree {
    struct Node {
        int mn, mx;
        ll sum = 0;
        int new_max = 0;

        Node() = default;

        explicit Node(int x) : mn(x), mx(x) {}

        Node(const Node &a, const Node &b) {
            sum = a.sum + b.sum;
            mn = min(a.mn, b.mn);
            mx = max(a.mx, b.mx);
        }
    };

    vector<Node> tree;
    int N = 1;

    SegmentTree(int sz) {
        while (N < sz)
            N *= 2;
        tree.resize(2 * N);
        for (int i = 1; i < 2 * N; i++)
            tree[i] = Node(0);
    }

    void push(int v, int tl, int tm, int tr) {
        if (tree[v].new_max == 0)
            return;
        if (v < N) {
            tree[2 * v].sum = 1LL * (tm - tl) * tree[v].new_max;
            tree[2 * v + 1].sum = 1LL * (tr - tm) * tree[v].new_max;
            tree[2 * v].mn = tree[2 * v + 1].mn = tree[2 * v].mx = tree[2 * v + 1].mx = tree[v].new_max;
            tree[2 * v].new_max = tree[2 * v + 1].new_max = tree[v].new_max;
        }
        tree[v].new_max = 0;
    }

    void push_max(int v, int tl, int tr, int l, int r, int x) {
        if (r <= tl || tr <= l || tree[v].mn >= x)
            return;
        if (l <= tl && tr <= r && tree[v].mx <= x) {
            tree[v].sum = 1LL * (tr - tl) * x;
            tree[v].mn = x;
            tree[v].mx = x;
            tree[v].new_max = x;
            return;
        }
        int tm = (tl + tr) / 2;
        push(v, tl, tm, tr);
        push_max(v * 2, tl, tm, l, r, x);
        push_max(v * 2 + 1, tm, tr, l, r, x);
        tree[v] = Node(tree[2 * v], tree[2 * v + 1]);
    }

    ll get(int v, int tl, int tr, int l, int r) {
        if (r <= tl || tr <= l)
            return 0;
        if (l <= tl && tr <= r)
            return tree[v].sum;
        int tm = (tl + tr) / 2;
        push(v, tl, tm, tr);
        ll ret = get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r);
        tree[v] = Node(tree[2 * v], tree[2 * v + 1]);
        return ret;
    }

    void push_max(int tl, int tr, int x) {
        push_max(1, 0, N, tl, tr, x);
    }

    ll get(int l, int r) {
        return get(1, 0, N, l, r);
    }
};

int solve() {
    if (!(cin >> n >> k))
        return 1;
    if (!n)
        return 1;
    SegmentTree seg(n);
    for (int i = 0; i < k; i++) {
        char x;
        cin >> x;
        if (x == '^') {
            int l, r, t;
            cin >> l >> r >> t;
            seg.push_max(l - 1, r, t);
        }
        if (x == '?') {
            int l, r;
            cin >> l >> r;
            ll ret = seg.get(l - 1, r);
            ll g = gcd(ret, r - l + 1);
            if ((r - l + 1) / g != 1)
                cout << ret / g << "/" << (r - l + 1) / g << '\n';
            else
                cout << ret / g << '\n';
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
