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
 
int a, k;

pair<int, int> kek(int x){
    int mn = 10;
    int mx = 0;
    do {
        int d = x % 10;
        mn = min(mn, d);
        mx = max(mx, d);
        x /= 10;
    } while (x > 0);
    return {mn, mx};
}
 
int solve() {
    if (!(cin >> a >> k))
        return 1;
    for (int i = 1; i < k; i++){
        auto [mn, mx] = kek(a);
        if (mn == 0)
            break;
        a += mn * mx;
    }
    cout << a << '\n';
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