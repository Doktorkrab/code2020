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
const int MAXN = 2e3 + 7;
int state[MAXN];
int sz[MAXN];
int color[MAXN];
bool used[MAXN];
bool comp_used[MAXN];
vector<int> g[MAXN];
int always;

bool check_parity(int v, int par = 1) { // 1|2
    if (comp_used[color[v]])
        return false;
    state[v] = par;
    used[v] = true;
    for (int u : g[v]) {
        if (state[u] == 0 && check_parity(u, 3 - par))
            return true;
        if (state[u] == state[v]) {
            always += sz[color[v]];
            comp_used[color[v]] = true;
            return true;
        }
    }
    return false;
}

void paint(int v, int c) {
    sz[c]++;
    color[v] = c;
    for (int u : g[v])
        if (color[u] != c)
            paint(u, c);
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> state[i];
    cin >> m;
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    int at_start = count(state, state + n, 1);
    fill(color, color + n, -1);
    int c = 0;
    for (int i = 0; i < n; i++)
        if (state[i] == 1 && color[i] == -1)
            paint(i, c++);

    for (int i = 0; i < n; i++) {
        if (!used[i] && state[i] == 1)
            check_parity(i, 1);
    }
    int ans1 = 0, ans2 = 0;
    for (int i = 0; i < n; i++) {
        if (color[i] == -1 || sz[color[i]] == 1 || comp_used[color[i]])
            continue;
        if (state[i] == 1)
            ans1++;
        else if (state[i] == 2)
            ans2++;
    }
    cout << max(at_start, always + max(ans1, ans2)) << '\n';
    return 1;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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
