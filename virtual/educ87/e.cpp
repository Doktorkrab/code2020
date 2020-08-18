
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
int n1, n2, n3;
const int MAXN = 5e3 + 5;
int c[2];
vector<int> g[MAXN];
int used[MAXN];
pair<int, int> comps[MAXN];
int p[MAXN][MAXN];
int dp[MAXN][MAXN];
int ch[MAXN];
int ans[MAXN];
int nc[MAXN];
int skip[MAXN];
bool dfs(int v, int cc, int num){
    c[cc]++;
    used[v] = cc;
    nc[v] = num;
    // cout << "!" << v + 1 << '\n';
    for (int u : g[v])
        if (used[u] == 1 - cc)
            continue;
        else if (used[u] == -1){
            if (dfs(u, 1 - cc, num))
                return 1;
        }
        else
            return 1;
    return 0;
}
void dfs1(int v, int num, int cl){
    used[v] = 1;
    // cout << "!" << v + 1 << ' ' << cl << ' ' << ch[num] << ' ' << num << '\n';
    if (cl == ch[num])
        ans[v] = 2;
    else if (n1 > 0){
        ans[v] = 1;
        n1--;
    }
    else 
        ans[v] = 3;
    for (int u : g[v]){
        if (!used[u])
            dfs1(u, num, 1 - cl);
    }
}
int solve() {
    if (!(cin >> n >> m >> n1 >> n2 >> n3))
        return 1;
    for (int i = 0; i < n; i++){
        g[i].clear();
    }
    for (int i = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    fill(used, used + n, -1);
    int now = 0;
    vector<int> small;
    for (int i = 0; i < n; i++){
        if (used[i] == -1){
            c[0] = c[1] = 0;
            if (dfs(i, 0, now)){
                cout << "NO\n";
                return 0;
            }
            comps[now++] = {c[0], c[1]};
        }
    }
    for (int i = 0; i <= now; i++)
        for (int j = 0; j <= n2; j++){
            dp[i][j] = 0;
            p[i][j] = -1;
        }
    dp[0][0] = 1;
    for (int i = 0; i < now; i++){
        for (int j = 0; j + comps[i].first <= n2; j++)
            if (!dp[i + 1][j + comps[i].first]){
                dp[i + 1][j + comps[i].first] |= dp[i][j];
                p[i + 1][j + comps[i].first] = 0;
            }
        for (int j = 0; j + comps[i].second <= n2; j++)
            if (!dp[i + 1][j + comps[i].second]){
                dp[i + 1][j + comps[i].second] |= dp[i][j];
                p[i + 1][j + comps[i].second] = 1;
            }
    }
    // for (int i = 0; i < now; i++)
    //     cout << skip[i] << " \n"[i + 1 == now];
    // for (int i = 0; i < now; i++){
    //     auto [x, y] = comps[i];
    //     cout << x << ' ' << y << '\n';
    // }
    // for (int i = 0; i <= now; i++)
    //     for (int j = 0; j <= n2; j++)
    //         cout << dp[i][j] << " \n"[j == n2];
    // for (int i = 0; i <= now; i++)
    //     for (int j = 0; j <= n2; j++)
            // cout << p[i][j] << " \n"[j == n2];
    if (!dp[now][n2]){
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    int x = now, y = n2;
    while (x > 0){
        // cout << "!!" << x << ' ' << y << ' ' << p[x][y] << '\n';
        ch[x - 1] = p[x][y];
        if (p[x][y])
            y -= comps[x - 1].second;
        else
            y -= comps[x - 1].first;
        x--;
    }
    fill(used, used + n, 0);
    now = 0;
    // cout << can << '\n';
    for (int i = 0; i < n; i++)
        if (!used[i]){
            if (!skip[now])
                dfs1(i, now, 0);
            else {
            }
            now++;

    }
    for (int i = 0; i < n; i++)
        cout << ans[i];
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