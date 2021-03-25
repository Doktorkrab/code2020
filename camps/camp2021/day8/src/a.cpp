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
const int MAXN = 1e6 + 1000;
int p[MAXN];
vector<int> g[MAXN];
pair<int, int> edges[2 * MAXN];
int pnt = 0;
inline void add_edge(int v, int u){
    g[v].push_back(u);
    g[u].push_back(v);
//    cout << v << ' ' << u << endl;
    edges[pnt++] = {v, u};
}
int solve() {
    pnt = 0;
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> p[i];
    for (int i = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        add_edge(v, u);
    }
    p[n] = p[n + 1] = p[n + 2] = p[n + 3] = 0;
    add_edge(n + 1, n + 2);
    add_edge(n + 3, n + 2);
    m++;
    for (int i = 0; i < n; i++){
        add_edge(i, n);
    }
    for (int i = 0; i < n; i++)
        add_edge(i, n + 1);
    vector<int> best;
    int sum = 0;
    for (int i = 0; i <= n + 3; i++)
        sort(RALL(g[i]), [&](int a, int b){ return p[a] < p[b]; });
    for (int i = 0; i < m; i++){
        auto [b, c] = edges[i];
        vector<int> edges_b{g[b].begin(), g[b].begin() + min(SZ(g[b]), 3)};
        vector<int> edges_c{g[c].begin(), g[c].begin() + min(SZ(g[c]), 3)};
        for (auto a : edges_b)
            for (auto d : edges_c)
                if (a != b && a != c && a != d && d != b && d != c){
                    int nn = p[a] + p[b] + p[c] + p[d];
//                    cout << a + 1 << ' ' << b + 1 << ' ' << c + 1 << ' ' << d + 1 << ' ' << nn << '\n';
                    if (nn > sum){
                        best = {a, b, c, d};
                        sum = nn;
                    }
                }

    }
    for (int x : {n, n + 1, n + 2, n + 3})
        if (count(ALL(best), x))
            best.erase(find(ALL(best), x));
    cout << SZ(best) << '\n';
    for (int x : best)
        cout << x + 1 << ' ';
    cout << '\n';
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
