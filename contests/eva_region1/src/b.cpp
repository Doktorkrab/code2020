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
const int MAXN = 2e5 + 7;
vector<pair<int, int>> g[MAXN];
set<int> g1[MAXN][2];
vector<int> have;
int used[MAXN];
bool dfs(int v, int now, int iter){
    used[v] = iter;
    have.push_back(v);
    if (SZ(have) == 5){
        cout << "5\n";
        for (int x : have)
            cout << x + 1 << " ";
        cout << '\n';
        return true;
    }
    bool res = false;
    if (SZ(g1[v][now])){
        int nxt = (*g1[v][now].begin());
        if (used[nxt] != iter)
            res = dfs(nxt, now ^ 1, iter);
    }
    have.pop_back();
    return res;
}
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < m; i++) {
        int v, u;
        char c;
        cin >> v >> u >> c;
        --v, --u;
        g[v].emplace_back(u, c);
        g[u].emplace_back(v, c);
        g1[v][c - 'a'].insert(u);
        g1[u][c - 'a'].insert(v);
    }
    for (int i = 0; i < n; i++) {
        if (SZ(g1[i][0]) >= 2) {
            cout << "3\n";
            cout << (*g1[i][0].begin()) + 1 << " " << i + 1 << ' ' << (*next(g1[i][0].begin())) + 1 << '\n';
            return 0;
        }

        if (SZ(g1[i][1]) >= 2) {
            cout << "3\n";
            cout << (*g1[i][1].begin()) + 1 << " " << i + 1 << ' ' << (*next(g1[i][1].begin())) + 1 << '\n';
            return 0;
        }
    }
    for (int i = 0; i < n; i++)
        if (dfs(i, 0, i + 1))
            return 0;
    cout << "-1\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
