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
 
int n;
const int MAXN = 1e5 + 7;
const int MAXLOG = 21;
vector<int> g[MAXN];
int bin_up[MAXLOG][MAXN];
int tin[MAXN];
int tout[MAXN];
int timer = 0;

inline bool is_anc(int a, int b) { // Is A ancestor B?
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

void precalc(int v, int p){
    bin_up[0][v] = p;
    for (int i = 1; i < MAXLOG; i++)
        bin_up[i][v] = bin_up[i - 1][bin_up[i - 1][v]];
    tin[v] = timer++;

    for (int u : g[v])
        if (u != p)
            precalc(u, v);

    tout[v] = timer++;
}

int get_lca(int a, int b){
    if (is_anc(a, b))
        return a;
    for (int i = MAXLOG - 1; i >= 0; i--){
        int v = bin_up[i][a];
        if (!is_anc(v, b))
            a = v;
    }
    // cerr << "lca completed\n";
    return bin_up[0][a];
}


int solve() {
    if (!(cin >> n))
        return 1;
    if (n == 0)
        return 1;
    // cout << "!" << n << '\n';
    for (int i = 0; i < n; i++){
        g[i].clear();
        tin[i] = tout[i] = -1;
        for (int j = 0; j < MAXLOG; j++)
            bin_up[j][i] = 0;
    }
    timer = 0;
    for (int i = 1; i < n; i++){
        int v, u;
        cin >> v >> u;
        g[--v].push_back(--u);
        g[u].push_back(v);
    }

    precalc(0, 0);
    // cerr << "precalc completed\n";
    int root = 0;
    int m;
    cin >> m;
    while (m--){
        char q;
        cin >> q;
        if (q == '!'){
            int x;
            cin >> x;
            root = x - 1;
            continue;
        }
        int a, b;
        cin >> a >> b;
        --a, --b;
        int l = get_lca(a, b);
        if (l == root || !is_anc(l, root)){
            cout << l + 1 << '\n';
            continue;
        }

        int l1 = get_lca(root, a);
        int l2 = get_lca(root, b);
        if (is_anc(l1, l2))
            swap(l1, l2);
        cout << l1 + 1 << '\n';
    }
    return 0;
}
 
signed main() {
#ifndef LOCAL
    freopen("dynamic.in", "r", stdin);
    freopen("dynamic.out", "w", stdout);
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