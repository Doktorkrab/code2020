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
 
int n, k;
const int MOD = 100000007;
int bin_p(int a, int b){
    int res = 1;
    while (b){
        if (b & 1)
            res = (a * res) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}
int rev(int a){
    //cout << a << ' ' << bin_p(a, MOD - 1) << '\n';
    return bin_p(a, MOD - 2);
}
int euler(int x){
    int result = x;
    //int gg = x;
    //int stop = ((int)sqrtl(x + 0.5)) + 1;
    for (int f = 2; f * f <= x; f++){
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
    int res = 0;
    for (int f = 2; f * f <= x; f++){
        if (x % f != 0)
            continue;
        res += euler(x / f);
        if (f != x / f)
            res += euler(f);
    }
    return res;
}

int ff(int x){
    int res = 0;
    for (int i = 1; i < x; i++)
        res += (gcd(x - i, i) == 1);
    return x;
}

int g1(int x){
    int res = 0;
    for (int f = 2; f * f <= x; f++){
        if (x % f != 0)
            continue;
        res += ff(x / f);
        if (f != x / f)
            res += ff(f);
    }
    return res;
}
int solve() {
    if (!(cin >> n >> k))
        return 1;
    //n %= MOD;
    //cout << euler(n) % MOD << '\n';
    //return 0;
    for (int i = 1; i <= k; i++){
        //if (i == 1 || i % 2 == 0)
            //n %= MOD;
        if (i % 2 == 1)
            n = euler(n);
        if (n == 1)
            break;
    }
    assert(n != 0);
    cout << n % MOD << '\n';
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

