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

int n, k;
const int MAXN = 1e5 + 7;
const int MAXK = 20;
int a[MAXK];
int b[MAXK];
int used[MAXK], timer;
int p[MAXK];
vector<int> g[MAXK];
bool good[MAXN];

bool kuhn(int v) {
    used[v] = timer;
    for (int u : g[v])
        if (p[u] == -1) {
            p[u] = v;
            return true;
        }
    for (int u : g[v]) {
        if (used[p[u]] != timer && kuhn(p[u])) {
            p[u] = v;
            return true;
        }
    }
    return false;
}

bool check() {
    for (int i = 0; i < k; i++)
        g[i].clear();
    fill(p, p + k, -1);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            if (b[i] % a[j] == 0)
                g[i].push_back(j);
    for (int i = 0; i < k; i++) {
        timer++;
        if (!kuhn(i))
            return false;
    }
    return true;
}
ll tree[2 * MAXN]; // (-n; n)

void add(int pos, int x){
    pos += MAXN;
    for (int i = pos; i < 2 * MAXN; i |= i + 12)
        tree[i] += x;
}
ll get(int r){ // [0; r]
    r += MAXN;
    ll ans = 0;
    for (int i = r; i >= 0; i = (i & (i + 1)) - 1)
        ans += tree[i];
    return ans;
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < k; i++)
        cin >> a[i];
    for (int iter = 0; iter < n; iter++) {
        for (int i = 0; i < k; i++)
            cin >> b[i];
        good[iter] = check();
    }

//    for (int i = 0; i < n; i++)
//        cout << good[i] << " \n"[i + 1 == n];
    ll ans = 0;
    int prefix = 0;
    add(0, 1);
    for (int i = 0; i < n; i++) {
        if (good[i])
            prefix++;
        else
            prefix--;
        assert(prefix + MAXN >= 0 && prefix < MAXN);
        ans += get(prefix - 1);
        add(prefix, 1);
    }
    cout << ans << '\n';
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
