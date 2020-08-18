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

 
int solve() {
    if (!(cin >> n))
        return 1;
    vector<ll> best(2, 0);
    best[0] = 1e9;
    // best[1] = 0;
    ll sum = 0;
    ll prefix = 0;
    ll best1 = 0;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        if (i % 2 == 0)
            sum += x;
        if (i & 1)
            prefix += x;
        else
            prefix -= x;
        // cout << prefix << ' ' << prefix - best[i % 2] << ' ' <<prefix - best[(i % 2) ^ 1] << '\n';
        best1 = max(best1, prefix - best[(i % 2)]);
        best[i % 2] = min(best[i % 2], prefix);
    }
    // cout << sum << ' ' << best1 << '\n';
    cout << sum + best1 << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
   cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}