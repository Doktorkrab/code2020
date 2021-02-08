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
const int MAXN = 205;
int p[MAXN];
int used[MAXN];
int run = 0;
vector<int> g[MAXN];

bool dfs(int v) {
    used[v] = run;
    for (int u : g[v])
        if (p[u] == -1) {
            p[u] = v;
            return true;
        }
    for (int u : g[v]) {
        if (used[p[u]] != run && dfs(p[u])) {
            p[u] = v;
            return true;
        }
    }
    return false;
}

int arr[MAXN][MAXN];

bool check(int x) {
    for (int i = 0; i < n; i++)
        g[i].clear();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] >= x)
                g[i].push_back(j);
        }
    }
    run = 0;
    fill(used, used + n, -1);
    fill(p, p + m, -1);
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
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];
//    cout << check(76) << '\n';
    int l = 0, r = 1e9 + 100;
    int best = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (arr[i][j] > best && check(arr[i][j]))
                best = arr[i][j];
    cout << best << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("k.in", "r", stdin);
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
