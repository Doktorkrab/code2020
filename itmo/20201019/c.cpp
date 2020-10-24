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

int n, q;
const int MAXN = 3e5 + 7;

struct SegmentTree {
    struct Node {
        int mx = TMIN(ll) / 2, mn = TMAX(ll) / 2;

        Node() = default;

        Node(int a) : mx(a), mn(a) {}

        Node(int a, int b) : mx(a), mn(b) {}

        void merge(const Node &a, const Node &b) {
            mx = max(a.mx, b.mx);
            mn = min(a.mn, b.mn);
        }
    };

    Node tree[4 * MAXN];
    int N;
    int _n;

    SegmentTree(int *arr, int n) {
        N = 1;
        _n = n - 1;
        while (N < n - 1)
            N *= 2;
        for (int i = 0; i + 1 < n; i++)
            tree[i + N] = Node(arr[i + 1] - arr[i]);
        for (int i = N - 1; i >= 0; i--)
            tree[i].merge(tree[2 * i], tree[2 * i + 1]);
    }

    void upd(int pos, int x) {
        if (pos < 0 || pos >= _n)
            return;
        tree[pos += N].mx += x;
        tree[pos].mn += x;
        pos /= 2;
        while (pos >= 1) {
            tree[pos].merge(tree[pos * 2], tree[pos * 2 + 1]);
            pos /= 2;
        }
    }

    Node get(int v, int tl, int tr, int l, int r) {
//        cout << v << ' ' << tl << ' ' << tr << ' ' << l << ' ' << r << '\n';
//        cout << tree[v].mx << ' ' << tree[v].mn << '\n';
//        cout << (tr <= l) << " " << (r <= tl) << '\n';
        if (tr <= l || r <= tl)
            return Node(-1e9, 1e9);
        if (l <= tl && tr <= r)
            return tree[v];
        int tm = (tl + tr) / 2;
        auto ret = Node();
        auto t1 = get(v * 2, tl, tm, l, r);
        auto t2 = get(v * 2 + 1, tm, tr, l, r);
        ret.merge(t1, t2);
        cout << "!!" << v << ' ' << tl << ' ' << tm << ' ' << tr << ' ' << l << ' ' << r << '\n';
        cout << '\t' << ret.mn << ' ' << ret.mx << '\n';
        cout << '\t' << t1.mn << ' ' << t1.mx << '\n';
        cout << '\t' << t2.mn << ' ' << t2.mx << '\n';
        return ret;
    }

    Node get(int l, int r) {
        return get(1, 0, N, l, r);
    }
};

int arr[MAXN];

int solve() {
    if (!(cin >> n >> q))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    SegmentTree seg(arr, n);
//    for (int i = 1; i < 2 * seg.N; i++)
//        cout << i << ' ' << seg.tree[i].mx << ' ' << seg.tree[i].mn << '\n';
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            --l;
            --r;
//            cout << l << ' ' << r << ' ' << seg.N << '\n';
            if (l <= r) {
                auto ret = seg.get(l, r);

                if (ret.mx <= 1)
                    cout << "YES\n";
                else
                    cout << "NO\n";
            } else {
                auto ret = seg.get(r, l);
                cout << ret.mn << ' ' << ret.mx << '\n';
                if (ret.mn >= -1)
                    cout << "YES\n";
                else
                    cout << "NO\n";
            }
        }
        if (type == 2) {
            int l, r, d;
            cin >> l >> r >> d;
            --l, --r;
            seg.upd(l - 1, d);
            seg.upd(l, -d);
            seg.upd(r, -d);
            seg.upd(r - 1, d);
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
