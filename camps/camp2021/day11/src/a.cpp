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
const int MAXN = 4e5 + 7;
vector<int> g[MAXN];
vector<int> g1[MAXN];
int dp[MAXN];
int p[MAXN];
int used[MAXN];

void dfs(int v) {
    used[v] = true;
    if (SZ(g[v]) == 0) {
        dp[v] = (v < n);
        return;
    }
    for (int u : g[v]) {
        if (!used[u])
            dfs(u);
        if (dp[u]) {
            dp[v] = true;
            p[v] = u;
        }
    }

}

bool dfs1(int v){
    used[v] = 1;
    for (int u : g1[v]) {
        if (used[u] == 1)
            return true;
        if (!used[u] && dfs1(u))
            return true;
    }
    used[v] = 2;
    return false;
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < 2 * n; i++)
        g[i].clear(), dp[i] = false;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        g[i].resize(x);
        g[i + n].resize(x);
        g1[i].resize(x);
        for (int j = 0; j < x; j++) {
            cin >> g[i][j];
            g1[i][j] = --g[i][j];
            g[i + n][j] = g[i][j];
            g[i][j] += n;
        }
    }
    int s;
    cin >> s;
    dfs(--s + n);
    if (dp[s + n]){
        cout << "Win\n";
        int now = s + n;
        while (SZ(g[now]) > 0){
            if (now >= n)
                cout << now + 1 - n << ' ';
            else
                cout << now + 1 << ' ';
            now = p[now];
        }
        if (now >= n)
            cout << now + 1 - n << '\n';
        else
            cout << now + 1 << '\n';
    }
    else {
        fill(used, used + n, 0);
        if (dfs1(s))
            cout << "Draw\n";
        else
            cout << "Lose\n";
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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
