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

struct Vector {
    ll x, y;

    Vector operator-(const Vector &oth) const {
        return {x - oth.x, y - oth.y};
    }

    ll len2() {
        return x * x + y * y;
    }
};

struct Circle {
    Vector center;
    ll r;
};
const int MAXN = 5e3 + 7;
Circle have[MAXN];
int ans[MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> have[i].center.x >> have[i].center.y >> have[i].r;
    }
    fill(ans, ans + n, -1);
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++)
            if (ans[j] == -1 && (v == -1 || have[v].r < have[j].r))
                v = j;
        for (int j = 0; j < n; j++)
            if (ans[j] == -1 &&
                (have[j].center - have[v].center).len2() <= (have[v].r + have[j].r) * (have[v].r + have[j].r))
                ans[j] = v + 1;
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << " \n"[i + 1 == n];
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