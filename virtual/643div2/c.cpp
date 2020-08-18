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
 
int a, b, c, d;
const int MAXN = 3e6 + 7;
ll p[MAXN];
int solve() {
    if (!(cin >> a >> b >> c >> d))
        return 1;
    for (int i = 0; i <= b + c + 100; i++)
        p[i] = 0;

    for (int i = a; i <= b; i++){
        p[i + b]++;
        p[i + c + 1]--;
    }
    for (int j = 0; j < 2; j++)
        for (int i = 1; i <= max(b + c, d) + 100; i++)
            p[i] += p[i - 1];
    // for (int i = 0; i <= b + c + 10; i++)
    //     cout << p[i] << " ";
    // cout << '\n';
    ll ans = 0;
    for (int i = c; i <= d; i++){
        // cout << i << ' ' << p[b + c + 1] << ' ' << p[i] << '\n';
        ans += p[b + c + 1] - p[i];
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