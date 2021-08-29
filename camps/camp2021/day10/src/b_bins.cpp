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

const int MAXN = 1e4 + 7;
const int MAXK = 505;
const long double EPS = 1e-15;
int n, m, k;
long double arr[MAXN];
long double prefix[MAXN];
int p[MAXN];

struct SegmentTree {
    pair<long double, int> nodes[4 * MAXK];
    pair<long double, int> nodes1[4 * MAXK];
    int N;

    SegmentTree() = default;

    SegmentTree(int sz) {
        N = 1;
        while (N < sz)
            N *= 2;
        clear();
    }

    void clear() {
        fill(nodes, nodes + 2 * N, make_pair(1e30, -1));
        fill(nodes1, nodes1 + 2 * N, make_pair(1e30, -1));
    }

    void upd(int v, int tl, int tr, int pos, const pair<long double, int> &x) {
        if (pos < tl || tr <= pos)
            return;
        if (tr - tl == 1) {
            nodes[v] = min(nodes[v], x);
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, pos, x);
        upd(v * 2 + 1, tm, tr, pos, x);
        nodes[v] = min(nodes[v * 2], nodes[v * 2 + 1]);
    }

    pair<int, int> get(int v, int tl, int tr, long double looking) {
        if ((looking - nodes[v].first) < -EPS)
            return {-1, -1};
        if (tr - tl == 1)
            return {tr, nodes[v].second};
        int tm = (tl + tr) / 2;
        if (looking - nodes[2 * v + 1].first > -EPS)
            return get(v * 2 + 1, tm, tr, looking);
        return get(v * 2, tl, tm, looking);
    }

    void upd(int pos, const pair<long double, int> &x) {
        upd(1, 0, N, pos, x);
    }

    pair<int, int> get(long double a) {
        return get(1, 0, N, a);
    }
};

SegmentTree st;

bool check(long double x) {
    st.clear();
    for (int i = 0; i < n; i++)
        arr[i] -= x;
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + arr[i];
    vector<int> mx(n + 1, -1);
    for (int i = 0; i <= n; i++)
        p[i] = -1;
    p[0] = 0;
    mx[0] = 0;
    for (int i = m; i <= n; i++) {
        if (mx[i - m] != -1 && mx[i - m] < k)
            st.upd(mx[i - m], make_pair(prefix[i - m], i - m));
        auto res = st.get(prefix[i]);
        if (res.first != -1) {
            p[i] = res.second;
            mx[i] = res.first;
        }
    }
    for (int i = 0; i < n; i++)
        arr[i] += x;

//    for (int i = 0; i <= n; i++)
//        cout << prefix[i] << " \n"[i == n];
//    for (int i = 0; i <= n; i++)
//        cout << p[i] << " \n"[i == n];
//    for (int i = 0; i <= n; i++)
//        cout << mx[i] << " \n"[i == n];
    return p[n] != -1 && mx[n] == k;
}

int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    st = SegmentTree(k);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
//    check(5);
//    return 0;
    long double l = 0, r = 1e9 + 7;
    for (int i = 0; i < 120; i++) {
        long double mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    check(l);
    vector<int> ans;
    int now1 = n;
//    cout << l << ' ' << r << '\n';
    while (now1 > 0) {
        assert(p[now1] != -1);
        ans.push_back(now1 - p[now1]);
        now1 = p[now1];
    }
    reverse(ALL(ans));
    for (int x : ans)
        cout << x << ' ';
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
