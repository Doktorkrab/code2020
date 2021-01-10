#pragma GCC optimize("O3")
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

int n, m;

const double pi = acos(-1.L);
const int MAXLOG = 16;
const int MAXN = 1 << MAXLOG;
const int MAXC = 7;
int inv[MAXC];

int bin_p(int a, int b) {
    int res = 1;
    for (; b > 0; b >>= 1) {
        if (b & 1)
            res = res * a % MAXC;
        a = a * a % MAXC;
    }
    return res;
}

void prepare_inv() {
    for (int i = 1; i < MAXC; i++) {
        inv[i] = bin_p(i, MAXC - 2);
    }
}

namespace fft {
    struct Complex{
        double a, b;
        Complex() {}
        Complex(double x) : a(x), b(0) {}
        Complex(double a, double b) : a(a), b(b) {}
        Complex operator*(const Complex& x) const {
            return Complex(a * x.a - b * x.b, b * x.a + a * x.b);
        }
        Complex& operator*=(const Complex& x)  {
            return (*this) = (*this) * x;
        }
        Complex operator+(const Complex& x) const {
            return {a + x.a, b + x.b};
        }

        Complex operator-(const Complex& x) const {
            return {a - x.a, b - x.b};
        }

    };
    using cd = Complex;
    int lg = 0;
    int bitreverse(int a){
        int y = 0;
        for (int i = 0; i < lg; i++){
            y *= 2;
            if ((a >> i) & 1)
                y++;
        }
        return y;
    }
    void fft(vector<cd> &a, bool is_inverse) {
        int coef = 1;
        if (is_inverse)
            coef = -1;
        for (int i = 0; i < SZ(a); i++) {
            int t = bitreverse(i);
            if (i < t)
                swap(a[i], a[t]);
        }
        for (int k = 2; k <= SZ(a); k *= 2) {
            double angle = 2. * pi / k * coef;
            cd w1(cos(angle), sin(angle));
            for (int i = 0; i < SZ(a); i += k) {
                cd w = 1;
                for (int j = 0; j < k / 2; j++) {
                    auto tmp = a[i + j];
                    auto tmp1 = a[i + j + k / 2] * w;
                    a[i + j] = tmp + tmp1;
                    a[i + j + k / 2] = tmp - tmp1;
                    w *= w1;
                }
            }
        }
    }

    void inv_fft(vector<cd> &a) {
        fft(a, true);
        for (auto &x : a)
            x *= 1. / SZ(a);
    }
    vector<cd> fa, fb;
    vector<ll> res;
    vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
        if (max(SZ(a), SZ(b)) < 2000){
            res.resize(SZ(a) + SZ(b));
            res.assign(SZ(a) + SZ(b), 0);
            for (int i = 0; i < SZ(a); i++)
                for (int j = 0; j < SZ(b); j++)
                    res[i + j] = (res[i + j] + a[i] * b[j] % MAXC) % MAXC;
            return res;
        }
        int sz = 1;
        lg = 0;
        while (sz < SZ(a) + SZ(b))
            sz *= 2, lg++;
        fa.resize(sz);
        fa.assign(sz, 0);
        for (int i = 0; i < SZ(a); i++)
            fa[i] = a[i];
        fb.resize(sz);
        fb.assign(sz, 0);

        for (int i = 0; i < SZ(b); i++)
            fb[i] = b[i];
        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < sz; i++)
            fa[i] *= fb[i];
        res.resize(SZ(a) + SZ(b));
        inv_fft(fa);
        for (int i = 0; i < SZ(a) + SZ(b); i++) {
            res[i] = lround(fa[i].a);
            res[i] %= MAXC;
            res[i] = (MAXC + res[i]) % MAXC;
        }
        return res;
    }

} // namespace fft

vector<ll> divide(vector<ll> &p) {
    vector<ll> A(1);
    vector<ll> tmp1;
    A[0] = inv[p[0]];
    for (int sz = 1; sz < n - m + 1; sz <<= 1) {
        tmp1 = fft::multiply(p, A);
        tmp1[0] = (2 + MAXC - tmp1[0]) % MAXC;
        for (int i = 1; i < SZ(tmp1); i++)
            tmp1[i] = (MAXC - tmp1[i]) % MAXC;
        A = fft::multiply(tmp1, A);
        A.resize(2 * sz);
    }
    return A;
}

int solve() {
    if (!(cin >> n))
        return 1;
    vector<ll> kek = {1};
    vector<ll> lol = {1};
    auto keke = fft::multiply(kek, lol);
    vector<ll> a(n + 1);
    for (int i = 0; i <= n; i++)
        cin >> a[i];
    cin >> m;
    vector<ll> b(m + 1);
    for (int i = 0; i <= m; i++)
        cin >> b[i];
    if (n < m) {
        cout << "0 0\n" << n << ' ';
        for (int i = 0; i <= n; i++)
            cout << a[i] << " \n"[i == n];
        return 0;
    }
    auto ret = divide(b);
    vector<ll> c = fft::multiply(a, ret);
    int pnt = max(n - m, 0);
    cout << pnt << ' ';
    for (int i = 0; i <= pnt; i++) {
        cout << c[i] << " \n"[i == pnt];
    }
    fill(c.begin() + pnt + 1, c.end(), 0);
    reverse(c.begin(), c.begin() + pnt + 1);
    reverse(b.begin(), b.begin() + m + 1);
    reverse(a.begin(), a.begin() + n + 1);
    c = fft::multiply(b, c);
    for (int i = 0; i <= m; i++) {
        c[i] = (2 * MAXC + a[i] - c[i]) % MAXC;
    }
    pnt = max(m - 1, 0);
    while (pnt > 0 && c[pnt] == 0)
        pnt--;
    cout << pnt << ' ';
    for (int i = 0; i <= pnt; i++)
        cout << c[pnt - i] << " \n"[i == pnt];
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    prepare_inv();
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