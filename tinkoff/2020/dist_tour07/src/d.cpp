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

int n, m, q;
const int MAXN = 10;
vector<pair<int, int>> g[MAXN];
bool close[MAXN];
int w[2][MAXN];

int get() {
    int best = TMIN(int);
    for (int mask = 0; mask < (1 << n); mask++) {
        int now = 0;
        for (int i = 0; i < n; i++)
                if (!close[i])
                    now += w[(mask >> i) & 1][i];
        for (int v = 0; v < n; v++)
            for (auto[u, ww] : g[v])
                if (!close[v] && !close[u] && ((mask >> v) & 1) != ((mask >> u) & 1))
                    now -= ww;
//        cout << mask << ' ' << now << '\n';
        if (best < now)
            best = now;
    }
    return best;
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < n; j++)
            cin >> w[i][j];
    for (int i = 0; i < m; i++) {
        int v, u, ww;
        cin >> v >> u >> ww;
        g[--v].emplace_back(--u, ww);
    }
    cout << get() << '\n';
    cin >> q;
    for (int i = 0; i < q; i++) {
        int type, x;
        cin >> type;
        if (type == 3) {
            for (int j = 0; j < n; j++)
                close[j] = 0;
            continue;
        }
        if (type == 4) {
            for (int j = 0; j < n / 5; j++)
                close[j] = 1;
            continue;
        }
        cin >> x;
        if (type == 1) {
            close[x - 1] = 0;
            cout << get() << '\n';
        } else {
            close[x - 1] = 1;
            cout << get() << '\n';
        }
    }
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
