#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
//#define int ll

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
const int MAXN = 1e4;
const int MOD = 1e9 + 7;
int cnt[MAXN];

bool check(int x) {
    for (ll f = 2; f * f <= x; f++) {
        if (x % f != 0)
            continue;
        return false;
    }
    return true;
}

int bp(int a, int b){
    int res = 1;
    while (b > 0){
        if (b & 1)
            res = (1LL * res * a) % MOD;
        a = (1LL * a * a) % MOD;
        b >>= 1;
    }
    return res;
}

int solve(vector<pair<int, int>>& x, int p){
    if (SZ(x) < p)
        return 0;
    vector<vector<pair<int, int>>> y(p);
    for (auto [a, b] : x)
        y[a % p].push_back({a / p, b});
    for (int i = 0; i < p; i++)
        if (!SZ(y[i]))
            return 0;
    int ans = TMAX(int);
    for (int i = 0; i < p; i++){
        int sm = 0;
        for (auto [i, j] : y[i])
            sm += j;
        sm += solve(y[i], p);
        ans = min(sm, ans);
    }
    return ans;
}
int solve() {
    if (!(cin >> n))
        return 1;

    int ans = 1;
    vector<pair<int, int>> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i].second, arr[i].first = i;
    for (int i = 2; i <= 10000; i++) {
        if (!check(i))
            continue;
//        cout << i << ' ' << solve(arr, i) << '\n';
        ans = (1LL * ans * bp(i, solve(arr, i))) % MOD;
    }
    cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("h.in", "r", stdin);
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
