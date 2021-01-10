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

int k, m;
const int MOD = 1e9 + 7;

int bin_p(int a, int b){
    int ret = 1;
    while (b > 0){
        if (b & 1)
            ret = (1LL * a * ret) % MOD;
        a = (1LL * a * a) % MOD;
        b >>= 1;
    }
    return ret;
}

inline int get_inverse(int x){
    return bin_p(x, MOD - 2);
}

struct Poly {
    vector<ll> coef;

    Poly() = default;

    explicit Poly(int x) : coef(x) {}

    Poly operator-(const Poly &oth) {
        Poly ret(max(SZ(coef), SZ(oth.coef)));
        for (int i = 0; i < max(SZ(coef), SZ(oth.coef)); i++) {
            ret.coef[i] = 0;
            if (i < SZ(coef))
                ret.coef[i] += coef[i];
            if (i < SZ(oth.coef))
                ret.coef[i] -= oth.coef[i];
            ret.coef[i] = (MOD + ret.coef[i] % MOD) % MOD;
        }
        return ret;
    }

    Poly operator+(const Poly &oth) {
        Poly ret(max(SZ(coef), SZ(oth.coef)));
        for (int i = 0; i < max(SZ(coef), SZ(oth.coef)); i++) {
            ret.coef[i] = 0;
            if (i < SZ(coef))
                ret.coef[i] += coef[i];
            if (i < SZ(oth.coef))
                ret.coef[i] += oth.coef[i];
            ret.coef[i] = (MOD + ret.coef[i] % MOD) % MOD;
        }
        return ret;
    }

    Poly shift(int x) {
        Poly ret(x + SZ(coef));
        for (int i = 0; i < SZ(coef); i++)
            ret.coef[x + i] = coef[i];
        return ret;
    }
    Poly operator*(const Poly& b){
        Poly ret(SZ(coef) + SZ(b.coef));
        for (int i = 0; i < SZ(coef); i++)
            for (int j = 0; j < SZ(b.coef); j++) {
                ret.coef[i + j] += coef[i] * b.coef[j] % MOD;
                ret.coef[i + j] %= MOD;
            }
        return ret;
    }
    Poly operator*(ll x){
        Poly ret = (*this);
        for (ll& y : ret.coef)
            y = (1LL * x * y) % MOD;
        return ret;
    }
    Poly inverse(int l) const {
        Poly ret(l + 1);
        assert(coef[0] != 0);
        int inv = get_inverse(coef[0]);
        ret.coef[0] = inv;
        for (int i = 1; i <= l; i++){
            for (int j = 0; j < l; j++)
                ret.coef[i] = (ret.coef[i] + 1LL * ret.coef[j] * coef[i - j] % MOD) % MOD;
            ret.coef[i] = (1LL * ret.coef[i] * inv) % MOD;
        }
        return ret;
    }
    Poly operator/ (const Poly& oth){
        if (SZ(coef) < SZ(oth.coef))
            return Poly(0);
        return (*this) * oth.inverse(SZ(coef) - SZ(oth.coef) + 1);
    }
};


Poly multiply(Poly a, Poly b) {
    if (SZ(a.coef) <= 64) {
        return a * b;
    }
    int tm = SZ(a.coef) / 2;
    int tm1 = SZ(a.coef) - tm;
    Poly a0(tm), a1(tm1), b0(tm), b1(tm1);
    for (int i = 0; i < tm; i++) {
        a0.coef[i] = a.coef[i];
        b0.coef[i] = b.coef[i];
    }
    for (int i = tm; i < SZ(a.coef); i++) {
        a1.coef[i - tm] = a.coef[i];
        b1.coef[i - tm] = b.coef[i];
    }
    Poly a0b0 = multiply(a0, b0);
    Poly a1b1 = multiply(a1, b1);
    return a0b0 + a1b1.shift(2 * tm) + (multiply(a0 + a1, b0 + b1) - a0b0 - a1b1).shift(tm);
}

const int MAXN = 2e3 + 7;
int arr[MAXN];
int dp[MAXN];
int dp_leaves[MAXN];

int solve() {
    if (!(cin >> k >> m))
        return 1;
    for (int i = 0; i < k; i++)
        cin >> arr[i];
    dp[0] = 1;
    dp_leaves[0] = 1;
    for (int i = 1; i <= m; i++){
        for (int j = 0; j < k; j++){
            int need = i - arr[j];
            if (need < 0)
                continue;
            dp[i] = (dp[i] + dp_leaves[need]) % MOD;
        }
        for (int j = 0; j < i && i + j <= m; j++) {
            dp_leaves[i + j] += (1LL * dp[j] * dp[i]) % MOD * 2LL % MOD;
            dp_leaves[i + j] %= MOD;
        }
        if (2 * i <= m) {
            dp_leaves[2 * i] += (1LL * dp[i] * dp[i]) % MOD;
            dp_leaves[2 * i] %= MOD;
        }
    }
    for (int i = 1; i <= m; i++)
        cout << dp[i] << " \n"[i == m];
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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
