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
 
#define int ll
int n, k;
const int MOD = 100000007;
int f(int x){
    if (x == 1)
        return 1;
    int ans = 0;
    for (int a = 1; a < x; a++){
        if (gcd(x - a, a) == 1)
            ans++;
    }
    return ans % MOD;
}

int euler(int x){
    int result = x;
    //int gg = x;
    //int stop = ((int)sqrtl(x + 0.5)) + 1;
    for (int f = 2; 1LL * f * f <= x; f++){
        if (x % f == 0){
            result -= result / f;
        }
        while (x % f == 0)
            x /= f;
        //cout << f * f << ' ' << (f + 1) * (f + 1) << '\n';
    }
    if (x > 1){
        result -= result / x;
    }
    return result;
}
int g(int x){
    int ans = 0;
    for (int a = 1; a * a <= x; a++){
        if (x % a)
            continue;
        //cout << f(x / a) << ' ' << f(a) << '\n';
        ans = (ans + f(x / a)) % MOD;
        if (x / a != a)
            ans = (ans + f(a)) % MOD;
    }
    return ans;
}

int g1(int x){
    int res = 0;
    for (int f = 2; f * f <= x; f++){
        if (x % f != 0)
            continue;
        res += euler(x / f) % MOD;
        if (f != x / f)
            res += euler(f) % MOD;
        res %= MOD;
    }
    return res;
}
int rec(int a, int b){
    //cerr << b << '\n';
    if (b == 1){
        int gg = g(a);
        int ff = f(gg);
        //cout << gg << ' ' << g1(a) << ' ' << ff << '\n';
        return ff;
    }
    int ret = 0;
    if (b & 1)
        ret = f(rec(a, b - 1));
    else 
        ret = g(rec(a, b - 1));
    //cerr << "!" << b << '\n';
    return ret;
}
 
int solve() {
    if (!(cin >> n >> k))
        return 1;
    cout << rec(n, k) << '\n';
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
