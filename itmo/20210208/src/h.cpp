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
 
int n;
const int MAXN = 5e6 + 10;
int d[MAXN];
vector<int> primes;
struct Fraction{
    ll p, q;
    Fraction() = default;
    Fraction(ll a, ll b) : p(a), q(b) {
        ll g = gcd(p, q);
        p /= g;
        q /= g;
    }
    Fraction operator-(const Fraction& oth) const {
        return Fraction(p * oth.q - oth.p * q, q * oth.q);
    }

};
ostream& operator<<(ostream& os, const Fraction& f){
    os << f.p << "/" << f.q;
    return os;
}
bool check(int x){
    if (x < 2)
        return false;
    for (int f = 2; 1LL * f * f <= x; f++)
        if (x % f == 0)
            return false;
    return true;
}

int solve() {
    if (!(cin >> n))
        return 1;
//    fill(d, d + MAXN, -1);
//    for (int i = 2; i < MAXN; i++){
//        if (d[i] == -1){
//            d[i] = i;
//            primes.push_back(i);
//        }
//        for (int x : primes){
//            if (x > d[i] || 1LL * x * i >= MAXN)
//                break;
//            d[x * i] = x;
//        }
//    }
    if (check(n + 1)){
        cout << Fraction(1, 2) - Fraction(1, n + 1) << '\n';
        return 0;
    }
    int l = -1;
    int r = -1;
    for (int i = n - 1; i >= 0; i--){
        if (check(i + 1)){
            l = i;
            break;
        }
    }
    for (int i = n + 1; ; i++){
        if (check(i + 1)){
            r = i;
            break;
        }
    }
    cout << Fraction(1, 2) - Fraction(r - (n - l - 1), 1LL * (l + 1)*(r + 1)) << '\n';

//    for (int x = 1; x <= 100; x++){
//        cout << (*prev(upper_bound(ALL(primes), x))) << ' ' << (*upper_bound(ALL(primes), x)) << '\n';
//    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("h.in", "r", stdin);
#endif
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
