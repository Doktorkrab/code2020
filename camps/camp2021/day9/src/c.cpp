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
const int MAXC = 1e6 + 7;
const int MAXK = 21;
const ll INF = 1e12;
ll arr[MAXN];
ll dp[MAXK][MAXN];

void solve_n2() {
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= k; j++)
            dp[j][i] = INF;
    dp[0][0] = 0;
    for (int teams = 1; teams <= k; teams++) {
        for (int i = 0; i < n; i++) {
            ll mx = 0;
            ll sum = 0;
            for (int j = i + 1; j <= n; j++) {
                mx = max(mx, arr[j - 1]);
                sum += arr[j - 1];
                dp[teams][j] = min(dp[teams][j], dp[teams - 1][i] + (j - i) * mx - sum);
            }
        }
    }
    cout << dp[k][n] << '\n';
}

ll prefix_sums[MAXN];
ll prefix_max[MAXN];
ll suffix_max[MAXN];

void solvek2() {
    for (int i = 0; i < n; i++) {
        prefix_sums[i + 1] = prefix_sums[i] + arr[i];
        prefix_max[i + 1] = max(prefix_max[i], arr[i]);
    }
    suffix_max[n] = 0;
    for (int i = n - 1; i >= 0; i--)
        suffix_max[i] = max(suffix_max[i + 1], arr[i]);
    ll best = TMAX(ll);
    for (int i = 0; i <= n; i++) {
        ll now = i * prefix_max[i] + (n - i) * suffix_max[i] - prefix_sums[n];
        best = min(best, now);
    }
    cout << best << '\n';
}
struct Line {
    ll k, b;

    Line() : k(0), b(INF) {}

    Line(ll k, ll b) : k(k), b(b) {}

    ll operator()(ll x) const {
        return k * x + b;
    }
};
struct LiChao{


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

};
ll dp1[MAXN];
ll dp2[MAXN];
void solve_mono(){
    fill(dp1, dp1 + MAXN, INF);
    for (int i = 0; i < n; i++) {
        prefix_sums[i + 1] = prefix_sums[i] + arr[i];
    }
    fill(dp1, dp1 + MAXN, INF);
    LiChao liChao;
    dp1[0] = 0;
    for (int i = 0; i < n; i++)
        dp1[i + 1] = (i + 1) * arr[i] - prefix_sums[i + 1];

//    for (int j = 0; j <= n; j++)
//        cout << dp1[j] << " \n"[j == n];
    for (int i = 2; i <= k; i++){
        fill(liChao.nodes, liChao.nodes + 4 * MAXC, Line());
        for (int j = 0; j < i; j++)
            dp2[j] =INF;
        for (int j = i; j < n; j++){
            liChao.upd(1, 0, MAXC, Line(-j, dp1[j] + prefix_sums[j]));
            dp2[j + 1] = liChao.get(1, 0, MAXC, arr[j]) + (j + 1) * arr[j] - prefix_sums[j + 1];
        }
        for (int j = 0; j <= n; j++)
            dp1[j] = dp2[j];
//        for (int j = 0; j <= n; j++)
//            cout << dp1[j] << " \n"[j == n];
    }
    cout << dp1[n] << '\n';
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    if (is_sorted(arr, arr + n))
        solve_mono();
    else if (k == 2)
        solvek2();
    else if (n <= 2000)
        solve_n2();
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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
