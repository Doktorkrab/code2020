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
#define int ll
int n, m;
const int MAXN = 1e5 + 7;
int par[MAXN];

int get_ancestor(int v, int k) {
    if (k == 0 || v == 0)
        return v;
    return get_ancestor(par[v], k - 1);
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 1; i < n; i++)
        cin >> par[i];
    int a1, a2;
    int x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;
    ll sum = 0;
    int last = 0;
    for (int i = 0; i < m; i++) {
        int t = get_ancestor((a1 + last) % n, a2);
        sum += t;
//        cout << (a1 + last) % n << ' ' << a2 << ' ' << t << '\n';
        a1 = (1LL * x * a1 + y * a2 + z) % n;
        a2 = (1LL * x * a2 + y * a1 + z) % n;
        last = t;
    }
    cout << sum << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("m.in", "r", stdin);
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
