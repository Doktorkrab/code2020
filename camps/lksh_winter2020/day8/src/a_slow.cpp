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
};


Poly multiply(Poly a, Poly b) {
    if (SZ(a.coef) <= 64) {
        Poly ret(SZ(a.coef) + SZ(b.coef));
        for (int i = 0; i < SZ(a.coef); i++)
            for (int j = 0; j < SZ(b.coef); j++) {
                ret.coef[i + j] += a.coef[i] * b.coef[j] % MOD;
                ret.coef[i + j] %= MOD;
            }
        return ret;
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

int solve() {
    if (!(cin >> k >> m))
        return 1;
    Poly a(m + 1);
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        a.coef[x] = 1;
    }
//    a[0] = 1;
    Poly last = a;
    last.coef[0] = 1;

    for (int i = 1; i <= m; i++) {
        last = multiply(a, multiply(last, last));
        last.coef[0] = (last.coef[0] + 1) % MOD;
        last.coef.resize(m + 1);
    }
    for (int i = 1; i <= m; i++)
        cout << last.coef[i] << " \n"[i == m];
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
