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
int now[MAXN];
int tin[MAXN];
int tout[MAXN];
int timer;
int p[MAXN];
bool used[MAXN];
pair<pair<int, int>, pair<int, int>> butttons[MAXN];
vector<int> g[MAXN];

void precalc(int v, int p = -1){
    ::p[v] = p;
    tin[v] = timer++;
    for (int u : g[v]){
        if (u != p)
            precalc(u, v);
    }
    tout[v] = timer++;
}

bool is_anc(int a, int b){
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

bool check_color(int v, int c){
    return now[v] == 2 || now[v] == c;
}

bool check_path(int v, int u, int c){
    if (!check_color(v, c) || !check_color(u, c))
        return false;
    bool was_not_2 = (now[v] != 2) || (now[u] != 2);
    while (!is_anc(v, u)){
        if (!check_color(v, c))
            return false;
        was_not_2 |= (now[v] != 2);
        v = p[v];
    }
    while (v != u){
        if (!check_color(u, c))
            return false;
        was_not_2 |= (now[u] != 2);
        u = p[u];
    }
    if (!check_color(v, c))
        return false;
    was_not_2 |= (now[u] != 2);
//    cerr << "ok\n";
    return was_not_2;
}

void color_path(int v, int u){
    now[v] = now[u] = 2;
    while (!is_anc(v, u)){
        now[v] = 2;
        v = p[v];
    }
    while (v != u){
        now[u] = 2;
        u = p[u];
    }
    now[v] = 2;
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> now[i], g[i].clear();
    for (int i = 0; i < n - 1; i++){
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    precalc(0, 0);
    cin >> m;
    for (int i = 0; i < m; i++){
        int v, u, c;
        cin >> v >> u >> c;
        butttons[i] = {{v - 1, u - 1}, {c, i}};
    }
    mt19937 rnd(239);
//    shuffle(butttons, butttons + m, rnd);
    vector<int> ans;
    while (true){
        if (count(now, now + n, 1) == 0)
            break;
//        cerr << SZ(ans) << '\n';
        bool was = false;
        for (int i = 0; i < m; i++){
            auto [path, heh] = butttons[i];
            auto [c, index] = heh;
            auto [v, u] = path;
            if (!used[i] && check_path(v, u, c)){
                ans.push_back(index);
                color_path(v, u);
                was = true;
                used[i] = true;
                break;
            }
        }
        if (!was)
            break;
    }
    if (count(now, now + n, 1) != 0){
        cout << "-1\n";
        return 0;
    }
    cout << SZ(ans) << '\n';
    reverse(ALL(ans));
    for (int x : ans)
        cout << x + 1 << " ";
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("d.in", "r", stdin);
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