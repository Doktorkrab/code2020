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
const int MAXN = 3e4;
vector<int> g[MAXN];
string have;
string s;
vector<int> dp[MAXN];
int sz[MAXN];
int ls[MAXN];
ll ans = 0;

void dfs(int v) {
    sz[v] = 1;
    dp[v].resize(1);
    dp[v][0] = (have[v] == s[0]);
    ans += (dp[v][0]);
    if (have[v] < s[0])
        ls[v] = 1;
    else
        ls[v] = 0;
    for (int u : g[v]) {
        dfs(u);
        sz[v] += sz[u];
    }
    for (int u : g[v]) {
        for (int l = 0; l < SZ(dp[u]) && l + 1 < m; l++) {
            if (SZ(dp[v]) < l + 1)
                dp[v].push_back(0);
            if (have[v] > s[l + 1])
                continue;
            if (have[v] == s[l + 1]){
                ans += dp[u][l];
                dp[v][l + 1] += dp[u][l];
            }
        }
    }
}

int solve() {
    if (!(cin >> n >> m >> s >> have))
        return 1;
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        g[x - 1].push_back(i);
    }

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
