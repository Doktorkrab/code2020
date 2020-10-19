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
const ll MAXN = 2e5 + 7;
const ll MAXC = 1e9 + 7;

int arr[MAXN];

struct SegmentTree {
    struct Node {
        vector<int> sorted;
        vector<ll> prefix;

        Node() = default;

        explicit Node(int x) {
            sorted = {x};
            prefix = {0, x};
        }

        void merge(const Node &a, const Node &b) {
            sorted.resize(SZ(a.sorted) + SZ(b.sorted));
            prefix.resize(SZ(a.sorted) + SZ(b.sorted) + 1);
            std::merge(ALL(a.sorted), ALL(b.sorted), sorted.begin());
            prefix[0] = 0;
            for (int i = 0; i < SZ(sorted); i++)
                prefix[i + 1] = prefix[i] + sorted[i];
        }
    };

    int N;
    Node tree[4 * MAXN];

    SegmentTree(int *arr, int n) {
        N = 1;
        while (N < n)
            N *= 2;
        for (int i = 0; i < n; i++)
            tree[i + N] = Node(arr[i]);
        for (int i = N - 1; i >= 1; i--)
            tree[i].merge(tree[2 * i], tree[2 * i + 1]);
    }

    ll get(int v, int tl, int tr, int l, int r, ll mx) {
        if (tr <= l || r <= tl)
            return 0;
        if (l <= tl && tr <= r) {
            int pos = upper_bound(ALL(tree[v].sorted), mx) - tree[v].sorted.begin();
            return tree[v].prefix[pos];
        }
        int tm = tl + (tr - tl) / 2;
        return get(v * 2, tl, tm, l, r, mx) + get(v * 2 + 1, tm, tr, l, r, mx);
    }

    ll get(int l, int r, ll mx) {
        return get(1, 0, N, l, r, mx);
    }
};

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        arr[i] = x;
    }
    SegmentTree seg(arr, n);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        --l;
        ll ans = 1;
        int cnt = 0;
        while (ans < MAXC && seg.get(l, r, ans) >= ans) {
            ll t = seg.get(l, r, ans);
            ans = t + 1;
//            if (++cnt > 228)
//                break;
        }

        if (ans >= MAXC)
            ans = seg.get(l, r, MAXC) + 1;
        cout << ans << '\n';
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
