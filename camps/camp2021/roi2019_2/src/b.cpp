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

int n, m, k;
const int MAXN = 2e5 + 7;
int l[MAXN];
int r[MAXN];
vector<vector<int>> arr;

ll get(int h, int index) {
    if (h < l[index])
        return l[index] - h;
    if (h <= r[index])
        return 0;
    return h - r[index];
}

int solve() {
    if (!(cin >> m >> n >> k))
        return 1;
    arr.resize(m, vector<int>(2 * n));
    for (int i = 0; i < k; i++)
        cin >> l[i] >> r[i];
    ll ans = 0;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < 2 * n; j++)
            cin >> arr[i][j];
        sort(ALL(arr[i]));
    }
    for (int i = 0; i < n; i++){
        ll best = TMAX(ll);
        for (int j = 0; j < k; j++){
            ll now = 0;
            for (int x = 0; x < m; x++)
                now += get(arr[x][2 * i], j) + get(arr[x][2 * i + 1], j);
            best = min(best, now);
        }
        ans += best;
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
