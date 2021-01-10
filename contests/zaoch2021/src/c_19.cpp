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

int n, m, k, s;
const int MAXN = 2e5 + 7;
const ll INF = 1e18;
vector<pair<int, ll>> g[MAXN];
ll d[MAXN];
bool used[MAXN];

int solve() {
    if (!(cin >> n >> m >> k >> s))
        return 1;
    for (int i = 0; i < m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        g[v].emplace_back(u, w);
        g[u].emplace_back(v, w);
    }
    assert(k == 1);
    int one;
    cin >> one;
    fill(d, d + n, INF);
    d[0] = 0;
    set<pair<int, int>> have = {{0, 0}};
    while (SZ(have)) {
        auto[_, v] = (*have.begin());
        have.erase(have.begin());
        if (used[v])
            continue;
        used[v] = true;
        for (auto[u, w] : g[v]) {
            if (d[u] > d[v] + w) {
                d[u] = d[v] + w;
                have.insert({d[u], u});
            }
        }
    }
//    for (int i = 0; i < n; i++)
//        cout << d[i] << " \n"[i + 1 == n];
    vector<int> ans;
    for (int i = 0; i < n; i++)
        if (d[i] <= s)
            ans.push_back(i);
    cout << SZ(ans) << '\n';
    for (int i : ans)
        cout << i + 1 << ' ';
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
