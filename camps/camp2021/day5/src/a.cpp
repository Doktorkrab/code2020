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

template<int MAXSZ>
struct SegmentTree {
    pair<int, int> nodes[MAXSZ];
    int N = 1;

    SegmentTree(int sz) {
        while (N < sz)
            N *= 2;
        fill(nodes, nodes + 2 * N, make_pair(-1, -1));
    }

    void upd(int v, int tl, int tr, int pos, pair<int, int> x) {
        if (pos < tl || tr <= pos)
            return;
        if (tr - tl == 1) {
            nodes[v] = x;
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, pos, x);
        upd(v * 2 + 1, tm, tr, pos, x);
        nodes[v] = max(nodes[2 * v], nodes[2 * v + 1]);
    }

    pair<int, int> get(int v, int tl, int tr, int l, int r) {
        if (r <= tl || tr <= l)
            return {0, -1};
        if (l <= tl && tr <= r) {
            return nodes[v];
        }
        int tm = (tl + tr) / 2;
        return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
    }

    void upd(int pos, pair<int, int> x) {
        upd(1, 0, N, pos, x);
    }

    pair<int, int> get(int l, int r) {
        return get(1, 0, N, l, r);
    }
};

const int MAXN = 3e5 + 7;
int arr[MAXN];
int p[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    vector<int> compress(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        compress[i] = arr[i];
    }
    sort(ALL(compress));
    compress.resize(unique(ALL(compress)) - compress.begin());
    for (int i = 0; i < n; i++)
        arr[i] = (int) (lower_bound(ALL(compress), arr[i]) - compress.begin());
    SegmentTree<4 * MAXN> st(SZ(compress));
    for (int i = 0; i < n; i++) {
        pair<int, int> now = {1, -1};
        auto get = st.get(0, arr[i]);
        get.first++;
        now = max(now, get);
        p[i] = now.second;
//        cout << i << ' ' << compress[arr[i]] << ' ' << now.first << ' ' << now.second << '\n';
        now.second = i;
        st.upd(arr[i], now);
    }
    auto [ans, pos] = st.get(0, SZ(compress));
    cout << ans << '\n';
    vector<int> aa;
    while (pos >= 0){
        aa.push_back(compress[arr[pos]]);
        pos = p[pos];
    }
    reverse(ALL(aa));
    for (int i = 0; i < SZ(aa); i++)
        cout << aa[i] << " \n"[i + 1 == SZ(aa)];
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
