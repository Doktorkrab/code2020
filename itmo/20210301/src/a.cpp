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

unordered_map<int, int> have;
int solve() {
    if (!(cin >> n >> k))
        return 1;
    have.clear();
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        have[x]++;
    }
    ll ans = 0;
    for (auto [a, b] : have){
        ll nxt = k - a;
        if (k - a == a)
            ans += b - 1;
        else if (k - a > a && have.count(k - a)){
            ans += min(have[a], have[k - a]);
        }
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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
