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
 
ll n;
mt19937 rnd(239);

ll get_rand(ll a, ll b){
    return a + (rnd() % (b - a + 1));
}
ll pow_fast(ll a, ll b, ll mod){
    ll res = 1;
    unsigned __int128 bt = b;
    unsigned __int128 at = a;
    unsigned __int128 modt = mod;
    for (; bt > 0; bt >>= 1){
        if (bt & 1)
            res = (res * at) % modt;
        at = (at * at) % modt;
    }
    return res;
}
bool miller_rabin(ll x){
    if (x == 1 || x == 2)
        return true;
    ll m = x;
    ll s = 0;
    while (m % 2 == 0){
        s++;
        m /= 2;
    }
    for (int i = 0; i < 5; i++){
        ll t = get_rand(2, x - 1);
        ll cur = pow_fast(t, m, x);
        cout << "?" << cur << ' ' << x << ' ' << t << '\n';
        if (cur == 1 || cur == x - 1)
            continue;
        cout << '\t' << x << '\n';
        bool good = false;
        for (int j = 0; j < s - 1; j++){
            cur = pow_fast(cur, 2, x);
            cout << x << ' ' << m << ' ' << s << ' ' << cur << '\n';
            if (cur == 1)
                return false;
            if (cur == x - 1){
                good = true;
                break;
            }
        }
        if (!good)
            return false;
    }
    cout << "!!!!" << x << '\n';
    return true;
}
 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 1; i <= 32; i++)
        miller_rabin(i) << '\n';
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
