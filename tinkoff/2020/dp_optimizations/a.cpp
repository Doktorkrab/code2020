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

const int MAXN = 2e5 + 7;
const int MAXC = 1e6 + 7;
const ll INF = 1e18 + 7;
pair<int, int> arr[MAXN];
pair<int, int> sorted[MAXN];
ll dp[MAXN];
ll dp1[MAXN];

struct Line {
    ll k, b;

    Line() : k(0), b(INF) {}

    Line(ll k, ll b) : k(k), b(b) {}

    ll operator()(ll x) const {
        return k * x + b;
    }
};

Line tree[4 * MAXC];

ll get(int v, int tl, int tr, int x) {
    if (tr - tl == 1)
        return tree[v](x);
    int tm = (tl + tr) / 2;
    if (x < tm)
        return min(tree[v](x), get(v * 2, tl, tm, x));
    return min(tree[v](x), get(v * 2 + 1, tm, tr, x));
}

void add(int v, int tl, int tr, Line x) {
//    cerr << v << ' ' << tl << ' ' << tr << '\n';
    int tm = (tl + tr) / 2;
    bool mid = x(tm) < tree[v](tm);
    bool lft = x(tl) < tree[v](tl);
    if (mid)
        swap(x, tree[v]);
    if (tr - tl == 1)
        return;
    if (lft != mid)
        add(v * 2, tl, tm, x);
    else
        add(v * 2 + 1, tm, tr, x);
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i].first >> arr[i].second;
    sort(arr, arr + n, [&](const pair<int, int> &a, const pair<int, int> &b) {
        if (a.first != b.first)
            return a.first > b.first;
        return a.second < b.second;
    });
    int mx = 0;
    int pnt = 0;
    for (int i = 0; i < n; i++) {
        if (mx >= arr[i].second)
            continue;
        sorted[pnt++] = arr[i];
        mx = arr[i].second;
    }
    n = pnt;
//    dp1[0] = 0;
//    for (int i = 0; i < n; i++) {
//        dp1[i + 1] = INF;
//        for (int j = i; j >= 0; j--)
//            dp1[i + 1] = min(dp1[i + 1], 1LL * sorted[j].first * sorted[i].second + dp1[j]);
//    }
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        add(1, 0, MAXC, Line(sorted[i].first, dp[i]));
        dp[i + 1] = get(1, 0, MAXC, sorted[i].second);
    }
    cout << dp[n] << '\n';
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
