#pragma GCC optimize("O3")

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

int n, m, cnt = 0;

const int MAXC = 1000;
const int MAXN = 500;
vector<int> g[MAXN];
pair<int, int> points[MAXN];
pair<int, int> have[MAXC];
int p[MAXC];
int used[MAXN];
int run = 0;

inline ll get_len(const pair<int, int> &a, const pair<int, int> &b) {
    return (1LL * (a.first - b.first) * (a.first - b.first) +
            1LL * (a.second - b.second) * (a.second - b.second));
}

const double eps = 1e-7;

bool dfs(int v) {
    used[v] = run;
    for (int u : g[v]) {
        if (p[u] == -1) {
            p[u] = v;
            return true;
        }
    }
    for (int u : g[v]) {
        if (used[p[u]] != run && dfs(p[u])) {
            p[u] = v;
            return true;
        }
    }
    return false;
}

ll dist[MAXN][MAXC];

bool check(ll x) {
    for (int i = 0; i < n; i++)
        g[i].clear();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < cnt; j++) {
            if (x >= dist[i][j])
                g[i].push_back(j);
        }
    run = 0;
    fill(used, used + n, -1);
    fill(p, p + cnt, -1);
    for (int i = 0; i < n; i++) {
        if (!dfs(i))
            return false;
        run++;
    }
    return true;
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    cnt = 0;
    for (int i = 0; i < n; i++)
        cin >> points[i].first >> points[i].second;
    for (int i = 0; i < m; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        for (int j = 0; j < c; j++)
            have[cnt++] = {x, y};
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < cnt; j++) {
            dist[i][j] = get_len(points[i], have[j]);
        }
//    cout << check(3e6) << '\n';
    ll l = 0, r = 3e12;
    while (r - l > 1) {
        ll mid = (l + r) / 2;
//        ll << mid << ' ' << check(mid) << '\n';
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    cout << sqrtl(r) << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("m.in", "r", stdin);
#endif
    cout << setprecision(10) << fixed;
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
