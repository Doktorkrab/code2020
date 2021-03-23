#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define SZ(X) (int)(X).size()
#define ALL(X) (X).begin(), (X).end()
#define RALL(X) (X).rbegin(), (X).rend()
#define TMAX(X) numeric_limits<X>::max();
#define TMIN(X) numeric_limits<X>::min();

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1e9 + 7;

int add(int a, int b) {
    return ((a + b) % MOD + MOD) % MOD;
}

int mul(int a, int b) {
    return (1LL * a * b) % MOD;
}

const int INF = 1e18;

template<int MAXNODES>
struct SegmentTree {
    struct Node {
        pair<int, int> x = {-INF, -INF};
    };
    Node nodes[MAXNODES];

    Node merge(const Node &a, const Node &b) {
        return {max(a.x, b.x)};
    }

    int N;

    SegmentTree(int sz) {
        N = 1;
        while (N < sz)
            N *= 2;
    }


    void upd(int v, int tl, int tr, int pos, pair<int, int> x) {
        if (pos < tl || tr <= pos)
            return;
        if (tr - tl == 1) {
            nodes[v] = {x};
//            cout << v << ' ' << x.first << ' ' << x.second << '\n';
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, pos, x);
        upd(v * 2 + 1, tm, tr, pos, x);
        nodes[v] = merge(nodes[2 * v], nodes[2 * v + 1]);
    }

    Node get(int v, int tl, int tr, int l, int r) {
        if (tr <= l || r <= tl)
            return {{-INF, -INF}};
        if (l <= tl && tr <= r)
            return nodes[v];
        int tm = (tl + tr) / 2;
        return merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
    }

    void upd(int pos, pair<int, int> x) {
        upd(1, 0, N, pos, x);
    }

    pair<int, int> get(int l, int r) {
        return get(1, 0, N, l, r).x;
    }
};

int n;
const int MAXN = 3e5 + 7;
int arr[MAXN];
int b[MAXN];
int dp[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    SegmentTree<4 * MAXN> st(n);
    SegmentTree<4 * MAXN> st1(n + 1);
    int pnt = 0;
    fill(dp, dp + n, -INF);
    dp[0] = 0;
    st1.upd(0, {0, 0});
    for (int i = 0; i < n; i++){
        while (pnt > 0 && arr[st.get(pnt - 1, pnt).second] >= arr[i]) {
            pnt--;
        }
        int l = 0;
        if (pnt > 0)
            l = st.get(pnt - 1, pnt).second + 1;
        st.upd(pnt++, make_pair(st1.get(l, i + 1).first + b[i], i));
        dp[i + 1] = st.get(0, pnt).first;
        st1.upd(i + 1, {st.get(0, pnt).first, i + 1});
    }
    cout << dp[n] << '\n';
    return 0;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tests = 1;
    for (int test = 1; test <= tests; test++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "-----------\n";
#endif
    }
    return 0;
}
