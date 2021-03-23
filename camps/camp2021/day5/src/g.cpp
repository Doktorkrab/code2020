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
const int MAXN = 5e4 + 7;
const int MAXC = 1e6 + 7;
const ll INF = 1e18;
pair<int, int> arr[MAXN];
pair<int, int> rdy[MAXN];
ll dp[4 * MAXC];

struct Line {
    ll k, b;

    Line() : k(0), b(INF) {}

    Line(ll k, ll b) : k(k), b(b) {}

    ll operator()(ll x) const {
        return k * x + b;
    }
};

Line nodes[4 * MAXC];

void upd(int v, int tl, int tr, Line x) {
    int tm = (tl + tr) / 2;
    bool mid = x(tm) < nodes[v](tm);
    bool lft = x(tl) < nodes[v](tl);
    if (mid)
        swap(nodes[v], x);
    if (tr - tl <= 1)
        return;
    if (lft != mid)
        upd(v * 2, tl, tm, x);
    else
        upd(v * 2 + 1, tm, tr, x);
}

ll get(int v, int tl, int tr, int x) {
    if (tr - tl == 0)
        return 0;
    if (tr - tl == 1)
        return nodes[v](x);
    int tm = (tl + tr) / 2;
    if (x < tm)
        return min(get(v * 2, tl, tm, x), nodes[v](x));
    return min(get(v * 2 + 1, tm, tr, x), nodes[v](x));
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i].first >> arr[i].second;
    sort(arr, arr + n, [&](pair<int, int> a, pair<int, int> b) {
        if (a.first != b.first)
            return a.first > b.first;
        return a.second < b.second;
    });
    int pnt = 0;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        if (mx >= arr[i].second)
            continue;
        rdy[pnt++] = arr[i];
        mx = arr[i].second;
    }
    n = pnt;
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        upd(1, 0, MAXC, Line(rdy[i].first, dp[i]));
        dp[i + 1] = get(1, 0, MAXC, rdy[i].second);
    }
    cout << dp[n] << '\n';
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
