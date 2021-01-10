#pragma GCC optimize("O3")
//#pragma GCC target("avx")
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

int n;

Poly multiply(Poly a, Poly b) {
    if (SZ(a.coef) <= 64) {
        Poly ret(SZ(a.coef) + SZ(b.coef));
        for (int i = 0; i < SZ(a.coef); i++)
            for (int j = 0; j < SZ(b.coef); j++) {
//                cout << ret.coef[i + j] << ' ' << ret.coef[i + j] + a.coef[i] * b.coef[j] << '\n';
                ret.coef[i + j] += a.coef[i] * b.coef[j];
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

const int BASE = 1e4;
const int BASE_LEN = 4;
const int MAXN = 1 << 16;
vector<ll> get_number(string s) {
    if (s[0] == '-' || s[0] == '+')
        s.erase(s.begin());
    vector<ll> res(MAXN);
    reverse(ALL(s));
    ll x = 1;
    int pnt = 0;
    for (char c : s) {
        res[pnt] += x * (c - '0');
        x *= 10;
        if (x == BASE) {
            x = 1;
            pnt++;
        }
    }
    return res;
}

int solve() {
    string s, t;
    if (!(cin >> s >> t))
        return 1;
    int sign_s = 0;
    if (s[0] == '-') {
        sign_s = 1;
        s = s.substr(1);
    }
    int sign_t = 0;
    if (t[0] == '-') {
        sign_t = 1;
        t = t.substr(1);
    }
    Poly a(n), b(n);
    a.coef = get_number(s);
    b.coef = get_number(t);
    auto ret = multiply(a, b);
    ret.coef.push_back(0);
    for (int i = 0; i + 1 < SZ(ret.coef); i++) {
        ret.coef[i + 1] += ret.coef[i] / BASE;
        ret.coef[i] %= BASE;
    }
    int pnt = SZ(ret.coef) - 1;
    while (pnt > 0 && ret.coef[pnt] == 0)
        pnt--;
    if (sign_s ^ sign_t && (pnt != 0 || ret.coef[pnt] != 0))
        cout << "-";
    cout << ret.coef[pnt];
    for (int i = pnt - 1; i >= 0; i--)
        cout << setfill('0') << setw(BASE_LEN) << ret.coef[i];
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
#else
    freopen("multiply.in", "r", stdin);
    freopen("multiply.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
//#ifdef LOCAL
//        cout << "------------------------------\n";
//#endif
    }
}