#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
#define int ll

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
const int MAXN = 1e3 + 7;
const int MOD = 1e9 + 7;
int par[MAXN];
int arr[MAXN];
vector<int> g[MAXN];

void upd_p(int v, int x) {
    v = par[v];
    while (v != -1) {
        arr[v] += x;
        v = par[v];
    }
}

void upd_sub(int v, int x) {
    arr[v] += x;
    for (int u : g[v])
        upd_sub(u, x);
}

int get_sum(int v) {
    int sum = arr[v];
    for (int u : g[v]) {
        sum += get_sum(u);
        sum %= MOD;
    }
    return sum;
}

int sum_p(int v) {
    v = par[v];
    int sum = 0;
    while (v != -1) {
        sum += arr[v];
        sum %= MOD;
        v = par[v];
    }
    return sum;
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    par[0] = -1;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        par[i] = p;
        g[p].push_back(i);
    }
    for (int i = 0; i< n; i++)
        cin >> arr[i];
    cout << arr[n - 1] << ' ';
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        int sm = (sum_p(v) + get_sum(v)) % MOD;
        upd_p(u, sm);
        upd_sub(u, sm);
        cout << arr[n - 1] << " \n"[i + 1 == m];
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
