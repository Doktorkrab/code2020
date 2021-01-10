#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;


#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()

#define TMAX(type) numeric_limits<type>::max()
#define TMIN(type) numeric_limits<type>::min()
#define int ll
#ifdef LOCAL
#define ass(X) assert(X)
#else
#define ass(X) {}
#endif

int n, m, k, s;
const int MAXN = 2e5 + 7;
const int INF = 1e18;
vector<pair<int, int>> g[MAXN];
int p[MAXN];
int d[MAXN];
int used[MAXN];
int sz[MAXN];
int par[MAXN];
bool can_start[MAXN];

int get(int v) {
    if (p[v] == v)
        return v;
    return p[v] = get(p[v]);
}

void un(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b)
        return;
    if (sz[a] > sz[b])
        swap(a, b);
    sz[b] += sz[a];
    p[a] = b;
}

int solve() {
    if (!(cin >> n >> m >> k >> s))
        return 1;
    fill(d, d + n, INF);
    fill(sz, sz + n, 1);
    iota(p, p + n, 0);
    fill(used, used + n, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;

    for (int i = 0; i < m; i++) {
        int v, u, c;
        cin >> v >> u >> c;
        --v, --u;
        g[v].emplace_back(u, c);
        g[u].emplace_back(v, c);
    }

    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        q.emplace(0, x - 1);
        d[x - 1] = 0;
        can_start[x - 1] = true;
        par[x - 1] = x - 1;
    }

    while (SZ(q)) {
        auto[dd, v] = q.top();
        q.pop();
        if (used[v])
            continue;
//        cout << dd << ' ' << v << '\n';
        used[v] = 1;
        un(v, par[v]);
        for (auto[u, w] : g[v]) {
            if (d[u] < INF && d[u] + w + d[v] <= s)
                un(v, u);
            if (d[v] + w < d[u] && d[v] + w <= s) {
                d[u] = d[v] + w;
                q.emplace(d[u], u);
                par[u] = v;
            }
        }
    }
    int root = get(0);
    vector<int> new_start;
    for (int i = 0; i < n; i++) {
        if (root == get(i) && can_start[i])
            new_start.push_back(i);
    }
    fill(d, d + n, INF);
    for (int i : new_start) {
        q.emplace(0, i);
        d[i] = 0;
    }
    fill(used, used + n, 0);
    while (SZ(q)) {
        auto[_, v] = q.top();
        q.pop();
        if (used[v])
            continue;
        used[v] = true;
        for (auto[u, w] : g[v]) {
            if (d[u] > d[v] + w) {
                d[u] = d[v] + w;
                q.emplace(d[u], u);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
        if (d[i] <= s)
            ans++;
    cout << ans << '\n';
    for (int i = 0; i < n; i++)
        if (d[i] <= s)
            cout << i + 1 << " ";
    cout << '\n';
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
