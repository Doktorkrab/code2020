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

#define double long double
int k;
double n, s, e, w;
const int MAXN = 50;
bool used[2 * MAXN][2 * MAXN];

bool &get(int x, int y) {
    return used[x + MAXN][y + MAXN];
}

double ans;

void rec(int pos, int x, int y, double prop) {
    if (pos == k) {
        ans += prop;
        return;
    }
    if (!get(x + 1, y)) {
        get(x + 1, y) = true;
        rec(pos + 1, x + 1, y, prop * e);
        get(x + 1, y) = false;
    }
    if (!get(x, y + 1)) {
        get(x, y + 1) = true;
        rec(pos + 1, x, y + 1, prop * n);
        get(x, y + 1) = false;
    }
    if (!get(x - 1, y)) {
        get(x - 1, y) = true;
        rec(pos + 1, x - 1, y, prop * w);
        get(x - 1, y) = false;
    }
    if (!get(x, y - 1)) {
        get(x, y - 1) = true;
        rec(pos + 1, x, y - 1, prop * s);
        get(x, y - 1) = false;
    }
}

int solve() {
    ans = 0;
    if (!(cin >> k >> n >> s >> e >> w))
        return 1;
    n /= 100;
    s /= 100;
    e /= 100;
    w /= 100;
    get(0, 0) = true;
    rec(0, 0, 0, 1);
    cout << fixed << setprecision(20) << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
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
