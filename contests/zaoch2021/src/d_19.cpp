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
const int MAXN = 5e3;
vector<int> g[MAXN];
string s;
string have;

string now;
ll ans = 0;
void dfs(int v, int p = -1, bool less = false){
    if (!less && SZ(now) == m)
        return;
    if (!less && have[v] > s[SZ(now)])
        return;
    if (!less && have[v] < s[SZ(now)])
        less = true;
    now += have[v];
//    cout << now << ' ' << v + 1 << '\n';
    ans++;
    for (int u : g[v])
        if (u != p)
          dfs(u, v, less);
    now.pop_back();
}

 
int solve() {
    if (!(cin >> n >> m >> s >> have))
        return 1;
    for (int i = 1; i < n; i++){
        int x;
        cin >> x;
        --x;
        g[x].push_back(i);
        g[i].push_back(x);
//        cout << i + 1 << "<=>" << x + 1 << '\n';
    }
    for (int v = 0; v < n; v++)
        dfs(v, -1);
    cout << ans << '\n';
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
