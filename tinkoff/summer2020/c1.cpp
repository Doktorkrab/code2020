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
 
int a, b;

int check(int a, int b){
    int res = 0;
    while (a > 0 || b > 0){
        res += abs((a % 10) - (b % 10));
        a /= 10;
        b /= 10;
    }
    return res;
}
 
int solve() {
    if (!(cin >> a >> b))
        return 1;
    int ans = 0;
    const int MOD = 1e9+7;
    for (int i = a; i <= b; i++)
        for (int j = a; j <= b; j++)
            ans = (ans + check(i, j)) % MOD;
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
