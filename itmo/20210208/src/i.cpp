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
 
int d, n;
const int MAXN = 2e3 + 7;
const int MOD = 1e9 + 7;
vector<int> g[MAXN];
int arr[MAXN];
vector<int> have;
int dp[MAXN];
int mul(int a, int b){
    return 1LL * a * b % MOD;
}
int add(int a, int b){
    return (a + b) % MOD;
}
void dfs(int v, int root, int p = -1){
    dp[v] = 1;
    for (int u : g[v]){
        if (u == p || arr[u] > arr[root] || arr[root] - arr[u] > d || (arr[u] == arr[root] && u > root))
            continue;
        dfs(u, root, v);
        dp[v] = mul(dp[v], dp[u] + 1);
    }
}
int solve() {
    if (!(cin >> d >> n))
        return 1;
    have.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        have[i] = arr[i];
        g[i].clear();
    }
    sort(ALL(have));
    have.resize(unique(ALL(have)) - have.begin());
    for (int i = 1; i < n; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    int ans = 0;
    for (int i = 0; i < n; i++){
        fill(dp, dp + n, 0);
        dfs(i, i, i);
        ans = add(ans, dp[i]);
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("i.in", "r", stdin);
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
