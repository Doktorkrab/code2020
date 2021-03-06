#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
const int N = 5000000;
const int N0 = 100000;
const int inf = 1e9 + 7;
using ll = long long;
vector<int> g[N0];
vector<int> og[N0];
int ts[N];
int curts = 0;
int css[N];
int days;

void dfs(int v) {
    css[v] = -1;
    for (auto u : g[v / days]) {
        if (css[days * u + (v % days + 1) % days] == 0) {
            dfs(days * u + (v % days + 1) % days);
        }
    }
    ts[curts++] = v;
}

bool used[N];

void dfs3(int v) {
    used[v] = 1;
    for (auto u : g[v / days]) {
        if (used[days * u + (v % days + 1) % days] == 0) {
            dfs3(days * u + (v % days + 1) % days);
        }
    }
}

void dfs1(int v, int col) {
    css[v] = col;
    for (auto u : og[v / days]) {
        if (css[days * u + (v % days - 1 + days) % days] == -1) {
            dfs1(days * u + (v % days - 1 + days) % days, col);
        }
    }
}

int cnt1[N];
int dp[N];

void dfs2(int v) {
    ts[v] = 1;
    dp[v] = max(dp[v], cnt1[css[v]]);
    for (auto u : g[v / days]) {
        if (ts[days * u + (v % days + 1) % days] == -inf) {
            dfs2(days * u + (v % days + 1) % days);
        }
        if (css[days * u + (v % days + 1) % days] != css[v]) {
            dp[v] = max(dp[v], (int) (dp[days * u + (v % days + 1) % days] + cnt1[css[v]]));
        } else {
            dp[v] = max(dp[v], dp[days * u + (v % days + 1) % days]);
        }
    }
}

void solve() {
    int n, m, d, i, j;
    cin >> n >> m >> d;
    days = d;
    int u, v;
    for (i = 0; i < m; ++i) {
        cin >> u >> v;
        --u, --v;
        og[v].push_back(u);
        g[u].push_back(v);
    }
    for (i = 0; i < n * d; ++i) {
        if (css[i] == 0) {
            dfs(i);
        }
    }
    int cnt = 0;
    reverse(ts, ts + curts);
    for (auto u : ts) {
        if (css[u] == -1) {
            dfs1(u, cnt++);
        }
    }
    char c;
    for (i = 0; i < cnt; ++i) {
        dp[i] = -1;
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < d; ++j) {
            cin >> c;
            v = i * d + j;
            if (c == '1') {
                if (dp[css[d * i + j]] != i) {
                    cnt1[css[d * i + j]]++;
                }
                dp[css[d * i + j]] = i;
            }
        }
    }
    for (i = 0; i < n * d; ++i) {
        dp[css[i]] = cnt1[css[i]];
    }
    dfs3(0);
    //reverse(ts, ts + curts);
    for (i = 0; i < n * d; ++i) {
        v = ts[i];
        for (auto u : og[v / days]) {
            if (css[days * u + (v % days - 1 + days) % days] != css[v] &&
                used[days * u + (v % days - 1 + days) % days]) {
                dp[css[v]] = max(dp[css[v]], dp[css[days * u + (v % days - 1 + days) % days]] + cnt1[css[v]]);
            }
        }
    }
    for (i = 0; i < n * d; ++i) {
        v = ts[i];
        for (auto u : og[v / days]) {
            if (css[days * u + (v % days - 1 + days) % days] != css[v] &&
                used[days * u + (v % days - 1 + days) % days]) {
                dp[css[v]] = max(dp[css[v]], dp[css[days * u + (v % days - 1 + days) % days]] + cnt1[css[v]]);
            }
        }
    }
    int ans = 0;
    for (i = 0; i < N; ++i) {
        if (used[i]) {
            ans = max(ans, dp[css[i]]);
        }
    }
    cout << ans << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}
