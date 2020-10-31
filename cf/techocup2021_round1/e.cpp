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
 
int a, b, c, d;
int y;
int ans = 0;
void upd(int v){
    if (0 <= v && v < y) {
        int t = (-v * v * d * b + v * (2 * a - d * b) + 2 * a);
        ans = max(ans, t / 2);
    }
}
int dd(int a, int b){
    int c = -b;
    if (a > 0){
        return -((a + c - 1) / c);
    }
    if (a < 0) {
        return (-a) / (-b);
    }
}
int solve() {
    if (!(cin >> a >> b >> c >> d))
        return 1;
    ans = 0;
    if (a > b * c){
        cout << "-1\n";
        return 0;
    }
    y = (c + d - 1) / d - 1;
    int ver1 = (2 * a - d * b) / (2 * d * b);
    int ver2 = (2 * a - d * b + 2 * d * b - 1) / (2 * d * b);
    upd(0);
    upd(y - 1);
    upd(ver1);
    upd(ver2);

    if (a == b * c){
        cout << max(ans, a + y * c * b - (y * (y + 1) / 2 * d * b)) << '\n';
        return 0;
    }

    int l = 0, r = 1e18;

    while (r - l > 1){
        int m = (l + r) / 2;
        int lft = m + (y * (y + 1)) / 2 * d * b - y * c * b - a;
//        cout << lft << ' ' << (a - b * c) << ' ' << dd(lft, a - b * c) << '\n';
//        cout << m << ' ' << (m <= ans || dd(lft, a - b * c) >= y) << '\n';
        if (m <= ans || dd(lft, a - b * c) >= y)
            l = m;
        else
            r = m;
    }
//    cout << y << '\n';
//    cout << 5 + (y * (y + 1)) / 2 * d * b - y * c * b - a << '\n';
//    cout << dd(5 + (y * (y + 1)) / 2 * d * b - y * c * b - a, a - b * c) << '\n';
//    cout << ans << '\n';
    cout << l << '\n';
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
