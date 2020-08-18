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
 
int n, a, r, m;
const int MAXN = 3e5 + 7;
int h[MAXN];
int solve() {
    if (!(cin >> n >> a >> r >> m))
        return 1;
    map<int, int> have;
    ll lower = 0, upper = 0;
    int lc = 0;
    int uc = n;
    for (int i = 0; i < n; i++){
        cin >> h[i];
        upper += h[i];
    }

    have[(upper + n - 1) / n] = 0;
    have[upper / n] = 0;
    have[upper / n + 1] = 0;
    have[max(0LL, upper / n - 1)] = 0;
    for (int i = 0; i < n; i++)
        have[h[i]]++;
    m = min(m, a + r);
    ll ans = 9e18;
    for (const auto& [k, v] : have){
        upper -= (1LL) * k * v;
        lc += v;
        uc -= v;
        lower += 1LL * k * v;
        ll diff = lc * k - lower;
        ll diff1 = upper - uc * k;
        ll now = min(diff, diff1) * m;
        if (diff < diff1)
            now += (diff1 - diff) * r;
        else
            now += (diff - diff1) * a;
        ans = min(ans, now);
        // cout << now << ' ' << k << ' ' << lower << ' ' << upper << ' ' << lc << ' ' << uc << ' ' << k << ' ' << v << '\n';
    }
    cout << ans << '\n';



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