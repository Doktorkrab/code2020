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
 
int n, d, m;

 
int solve() {
    if (!(cin >> n >> d >> m))
        return 1;
    vector<int> small, big;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        if (x <= m)
            small.push_back(x);
        else
            big.push_back(x);
    }
    sort(ALL(big));
    sort(ALL(small));
    reverse(ALL(small));
    reverse(ALL(big));
    ll best = 0;
    ll cur = 0;
    ll now = 0;
    ll now1 = 0;
    ll gg = 0;
    for (int i : small)
        gg += i;
    best = gg;
    for (int i : big)
        now1 += i;
    for (int i = SZ(big) - 1; i >= 0; i--){
        ll dd = (1LL * d + 1) * (i) + 1;
        if (dd > n){
            now1 -= big[i];
            continue;
        }
        while (cur < SZ(small) && cur < n - dd)
            now += small[cur++];
        //cout << i + 1 << ' ' << now << ' ' << now1 << '\n';
        best = max(best, now + now1);
        now1 -= big[i];
    }
    cout << best << '\n';
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
