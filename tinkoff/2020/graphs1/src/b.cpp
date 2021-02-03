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

int n, v, run;
const int MAXN = 105;
int p[MAXN];
int used[MAXN];
vector<int> g[2 * MAXN];

struct Entry {
    int t, x, y;
};
Entry have[MAXN];
const double EPS = 1e-9;

bool check(int a, int b) {
    double len = sqrtl(1LL * (have[a].x - have[b].x) * (have[a].x - have[b].x) +
                       1LL * (have[a].y - have[b].y) * (have[a].y - have[b].y));
    return (have[b].t - have[a].t) / 60. - len / v >= -EPS;
}

bool dfs(int v) {
    used[v] = run;
    for (int u : g[v])
        if (p[u] == -1) {
            p[u] = v;
            return true;
        }
    for (int u : g[v])
        if (used[p[u]] != run && dfs(p[u])) {
            p[u] = v;
            return true;
        }
    return false;
}

int solve() {
    if (!(cin >> n >> v))
        return 1;
    for (int i = 0; i < n; i++) {
        int h, m;
        scanf("%d:%d %d %d", &h, &m, &have[i].x, &have[i].y);
        have[i].t = h * 60 + m;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && check(i, j))
                g[i].push_back(j);
        }
    }
    fill(used, used + n, -1);
    fill(p, p + n, -1);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dfs(i);
        run++;
    }
    cout << n - ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
#endif
//    ios::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);
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
