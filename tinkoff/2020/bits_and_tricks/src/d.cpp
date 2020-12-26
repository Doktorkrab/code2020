#include <bits/stdc++.h>
#include <ostream>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
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
const int MAXN = 31;
const int MOD = 1e9 + 7;
int ans = 0;

vector<int> g[MAXN];
unordered_map<int, int> mem;

int rec(int mask) {
    if (mask + 1 == (1 << n)) {
        ans++;
        ans %= MOD;
//        cout << ans << endl;
        return 1;
    }
    if (mem.count(mask)) {
        ans += mem[mask];
        if (ans >= MOD)
            ans -= MOD;
        return mem[mask];
    }
//    cout << bitset<30>(mask) << endl;
    int x = 0;
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1)
            continue;
        for (int u : g[i]) {
            if ((mask >> u) & 1)
                continue;
            x += rec(mask | (1 << i) | (1 << u));
            if (x >= MOD)
                x -= MOD;
        }
        break;
    }
    mem[mask] = x;
    return x;
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    mem.rehash((1 << 22));
    for (int i = 0; i < n; i++)
        g[i].clear();
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    rec(0);
    cout << ans << '\n';
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
