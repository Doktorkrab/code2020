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
const int MAXN = 1e4 + 7;
vector<int> g[MAXN];
int timer = 0;
int tin[MAXN], fup[MAXN];
bool used[MAXN];
set<int> ans;
int dfs(int v, int p){
    used[v] = true;
    tin[v] = fup[v] = ++timer;
    int cnt = 0;
    //cout << v + 1 << ' ' << p + 1 << '\n';;
    for (int u : g[v]){
        if (u == p)
            continue;
        if (used[u])
            fup[v] = min(tin[u], fup[v]);
        else {
            //cout << "!" << v + 1 << ' ' << u + 1 << '\n';
            fup[v] = min(fup[v], dfs(u, v));
            cnt++;
            if (fup[u] >= tin[v] && p != -1)
                ans.insert(v);
        }
    }
    if (p == -1 && cnt > 1)
        ans.insert(v);
    return fup[v];
}
 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    
    for (int i = 0; i < n; i++)
        g[i].clear();

    fill(used, used + n, 0);
    fill(tin, tin + n, 0);
    fill(fup, fup + n, 0);
    ans.clear();

    for (int i = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i, -1);
    cout << SZ(ans) << '\n';
    for (int i : ans)
        cout << i + 1 << ' ';
    cout << '\n';
    return 0;
}
 
signed main() {
    	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
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
