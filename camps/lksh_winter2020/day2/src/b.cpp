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
const int MAXN = 1e6 + 7;
int par[MAXN];
int max1[MAXN];
int max2[MAXN];
vector<int> g[MAXN];

int get(int x) {
    if (max1[x] == 0)
        return 1;
    return max(max1[x], max2[x] + 1);
}

void upd(int v, int x) {
    if (v == -1)
        return;
    int old = get(v);
    int &m1 = max1[v];
    int &m2 = max2[v];
    if (m1 < x) {
        m2 = m1;
        m1 = x;
    } else if (m2 < x) {
        m2 = x;
    }
    if (old != get(v))
        upd(par[v], get(v));
}

int solve() {
    if (!(cin >> n))
        return 1;
    n++;
    par[0] = -1;
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        par[i] = x - 1;
        upd(par[i], 1);
        cout << max1[0] << " \n"[i + 1 == n];
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
