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

int n, m, q;
const int MAXN = 2e5 + 7;
const int INF = 1e9;
vector<int> g[MAXN], g1[MAXN];
pair<int, int> edges[MAXN];
int d[MAXN];
bool used[MAXN];

void bfs() {
    fill(d, d + n, INF);
    fill(used, used + n, false);
    d[0] = 0;
    deque<int> q = {0};
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        if (used[v])
            continue;
        used[v] = true;
        for (int u : g[v])
            if (d[u] > d[v] + 1) {
                d[u] = d[v] + 1;
                q.push_back(u);
            }
    }
}

int bfs1(int v, int u) {
    if (d[v] == d[u]) // edge has no impact
        return 0;
    if (d[v] > d[u])
        swap(v, u);
    g1[v].push_back(u);
    int new_can = 0;
    if (!used[v])
        return 0;
    deque<int> q = {u};
    while (!q.empty()) {
        int x = q.front();
        q.pop_front();
        if (used[x])
            continue;
        used[x] = true;
        new_can++;
        for (int y : g1[x]) {
            if (!used[y])
                q.push_back(y);
        }
    }
    return new_can;
}
int queries[MAXN];
int order[MAXN];
int ans[MAXN];
int solve() {
    if (!(cin >> n >> m >> q))
        return 1;
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        edges[i] = {v, u};
        g[v].push_back(u);
        g[u].push_back(v);
    }
    bfs();
//    for (int i = 0; i < n; i++)
//        cout << d[i] << " \n"[i + 1 == n];
    fill(order, order + m, -1);
    for (int i = 0; i < q; i++){
        int x;
        cin >> x;
        order[x - 1] = i;
        queries[i] = x - 1;
    }
    int pnt = q;
    for (int i = 0; i < m; i++){
        if (order[i] == -1) {
            queries[pnt] = i;
            order[i] = pnt++;
        }
    }
    fill(used, used + n, false);
    int last = 0;
    used[0] = true;
    for (int i = m - 1; i >= 0; i--){
        auto [a, b] = edges[queries[i]];
        ans[i] = last;
        last += bfs1(a, b);
//        cout << last << ' ' << i << '\n';
    }
    for (int i = 0; i < q; i++)
        cout << n - 1 - ans[i] << '\n';
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
