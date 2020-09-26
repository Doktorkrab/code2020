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
 
string a, b;
const int MOD = 1e9 + 7;
int mul(int x, int y){
    return (x * y) % MOD;
}
int add(int x, int y){
    return (x + MOD + y) % MOD;
}
int solve() {
    if (!(cin >> a >> b))
        return 1;
    int n = max(SZ(a), SZ(b));
    reverse(ALL(a));
    while (SZ(a) < n)
        a += '0';
    reverse(ALL(a));
    
    int left = 1;
    int ans = 0;
    for (int i = 0; i < n; i++){
        cout << left << '\n';
        for (int x = 0; x < 10; x++){
            for (int y = 0; y < 10; y++){
                int to_ans = abs(x - y);
                int minus_x = (x < (a[i] - '0') ? -1 : 0) + (x > (b[i] - '0') ? -1 : 0);
                int minus_y = (y < (a[i] - '0') ? -1 : 0) + (y > (b[i] - '0') ? -1 : 0);
                cout << x << ' ' << y << ' ' << mul(to_ans, mul(add(left, minus_x), add(left, minus_y))) << '\n';
                ans = add(ans, mul(to_ans, mul(add(left, minus_x), add(left, minus_y)))); 
            }
        }
        left = add(mul(add(left, -1), 10), add(add(b[i] - '0', -(a[i] - '0')), 1));
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
