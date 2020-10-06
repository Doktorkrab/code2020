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
int cur_present = 0;
const int MAXN = 1e5 + 7;
int par[MAXN];
set<pair<int, int>> have[MAXN];


int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < cur_present; i++)
        par[i] = -1;
    cur_present = 0;
    for (int i = 0; i < n; i++)
        have[i].clear();
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        if (SZ(have[a]) == 0) {
            par[cur_present] = a;
            have[a].insert({i, cur_present++});
        }
        auto[_, top] = (*have[a].begin());
//        cout << a + 1 << "->" << b + 1 << ' ' << top << ' ' << par[top] << '\n';
        have[a].erase(have[a].begin());
        if (par[top] == b)
            cout << "YES\n";
        else
            cout << "NO\n";
        have[b].insert({i, top});
    }
    return 0;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}