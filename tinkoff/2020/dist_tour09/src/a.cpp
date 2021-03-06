#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;
#define int ll

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
 
int n, m, k;

const int MAXN = 1e6 + 7;
vector<int> g[MAXN];

int color[MAXN];
int sz[MAXN];
pair<int, int> edges[MAXN];
void paint(int v, int c){
    color[v] = c;
    sz[c]++;
    for (int u : g[v]){
        if (color[u] == -1)
            paint(u, c);
    }
}
int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    for (int i = 0; i < n; i++)
        g[i].clear();
    for (int i = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    fill(color, color + n, -1);
    fill(sz, sz + n, 0);
    int c = 0;
    for (int i = 0; i < n; i++)
        if (color[i] == -1)
            paint(i, c++);
    ll cnt = -m;
    for (int i = 0; i < c; i++)
        cnt += 1LL * (sz[i] - 1) * sz[i] / 2;
    cout << max(1LL, c - k) << ' ';
    vector<int> have{sz, sz + c};
    sort(ALL(have));
    k -= cnt;
    while (k > 0 && SZ(have) > 1){
        int x = have.back();
        have.pop_back();
        int y = have.back();
        have.pop_back();
        c--;
        k -= 1LL * x * y;
        have.push_back(x + y);
    }
    assert(c >= 1);
    cout << c << '\n';
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
