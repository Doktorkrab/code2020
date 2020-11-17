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
int k;

 
int solve() {
    if (!(cin >> n >> k))
        return 1;
    ll gg = k;
    ll ans = 0;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        if (k - x < 0)
            continue;
        if (k - x == 0){
            ans++;
        }
        k -= x;
        if (i + 1 < n && k == 0)
            k = gg;
    }
    cout << ans << '\n' << k << '\n';
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
