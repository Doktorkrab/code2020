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
vector<int> g[MAXN];
int color[MAXN];
int p[MAXN];

int find_parent(int v){
    if (p[v] == v)
        return v;
    return p[v] = find_parent(p[v]);
}
deque<int> q;
void merge(int a, int b){
    if (SZ(g[a]) > SZ(g[b]))
        swap(a, b);
    for (int x : g[a])
        g[b].push_back(x);
    g[a].clear();
    p[a] = b;
    if (SZ(g[b]) > 1)
        q.push_back(b);
}
 
int solve() {
    if (!(cin >> n >> m))
        return 1;
    iota(p, p + n, 0);
    for (int i = 0; i < n; i++){
        g[i].clear();
    }
    for (int i = 0; i < m; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
    }
    q.clear();
    for (int i = 0; i < n; i++){
        if (SZ(g[i]) > 1)
            q.push_back(i);
    }
    while (SZ(q)){
        int x = q.front();
        q.pop_front();
        while (SZ(g[x]) > 1){
            int a = find_parent(g[x].back());
            g[x].pop_back();
            int b = find_parent(g[x].back());
//            cout << a << ' ' << b << '\n';
            if (a == b)
                continue;
            merge(a, b);
        }
    }
    fill(color, color + n, -1);
    int c = 1;
    for (int i = 0; i < n; i++){
        int x = find_parent(i);
        if (color[x] == -1)
            color[x] = c++;
        cout << color[x] << '\n';
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
