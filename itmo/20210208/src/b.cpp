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
 
ll a, b, c;
const int MAX = 1e9;
 
int solve() {
    if (!(cin >> a >> b >> c))
        return 1;
    vector<ll> ans;
    for (int sum = 1; sum <= 100; sum++){
        ll x = 1;
        for (int j = 0; j < a; j++)
            x *= sum;
        ll y = b * x + c;
        if (y >= MAX || y <= 0)
            continue;
        ll t = y;
        ll d = 0;
        while (y > 0){
            d += y % 10;
            y /= 10;
        }
        if (d == sum)
            ans.push_back(t);
    }
    cout << SZ(ans) << '\n';
    for (ll x : ans)
        cout << x << ' ';
    cout << '\n';
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
