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

int n, q;
const int MAXN = 1e5 + 7;
const int BLOCK = 322;
vector<int> g[MAXN];
int color[MAXN];
map<int, int> cnt_c[MAXN], cnt_cnt[MAXN];
vector<pair<int, int>> queries[MAXN];
int ans[MAXN];

void dfs(int v, int p = -1) {
    cnt_c[v][color[v]] = 1;
    cnt_cnt[v][1] = 1;
    for (int u : g[v]) {
        if (u == p)
            continue;
        dfs(u, v);
        if (SZ(cnt_c[v]) < SZ(cnt_c[u])) {
            swap(cnt_c[v], cnt_c[u]);
            swap(cnt_cnt[v], cnt_cnt[u]);
        }
        for (auto[a, b] : cnt_c[u]) {
            cnt_cnt[v][cnt_c[v][a]]--;
            if (cnt_cnt[v][cnt_c[v][a]] <= 0)
                cnt_cnt[v].erase(cnt_c[v][a]);
            cnt_c[v][a] += b;
            cnt_cnt[v][cnt_c[v][a]]++;
        }
    }
    for (auto[x, i] : queries[v]) {
        for (auto[a, b] : cnt_cnt[v])
            if (a >= x) {
                ans[i] += b;
            }
    }
}

int solve() {
    if (!(cin >> n >> q))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> color[i];
    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        queries[a - 1].emplace_back(b, i);
    }
    dfs(0);
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("n.in", "r", stdin);
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
