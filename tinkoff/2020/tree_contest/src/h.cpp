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
namespace fft {
const double pi = acos(-1.L);

struct Complex {
    double a, b;

    Complex() {}

    Complex(double x) : a(x), b(0) {}

    Complex(double a, double b) : a(a), b(b) {}

    Complex operator*(const Complex &x) const {
        return Complex(a * x.a - b * x.b, b * x.a + a * x.b);
    }

    Complex &operator*=(const Complex &x) {
        return (*this) = (*this) * x;
    }

    Complex operator+(const Complex &x) const {
        return {a + x.a, b + x.b};
    }

    Complex operator-(const Complex &x) const {
        return {a - x.a, b - x.b};
    }
};

using cd = Complex;
int lg = 0;

int bitreverse(int a) {
    int y = 0;
    for (int i = 0; i < lg; i++) {
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
    if (max(SZ(a), SZ(b)) < 2000) {
        res.resize(SZ(a) + SZ(b));
        res.assign(SZ(a) + SZ(b), 0);
        for (int i = 0; i < SZ(a); i++)
            for (int j = 0; j < SZ(b); j++)
                res[i + j] = res[i + j] + a[i] * b[j];
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
    }
    return res;
}

} // namespace fft
int n;
const int MAXN = 5e4 + 7;
vector<int> g[MAXN];
bool used[MAXN];
int ans[MAXN];
int sz[MAXN];

int calc_sz(int v, int p) {
    sz[v] = 1;
    for (int u : g[v])
        if (u != p && !used[u])
            sz[v] += calc_sz(u, v);
    return sz[v];
}

int find_centroid(int v, int need, int p = -1) {
    for (int u : g[v])
        if (u != p && !used[u] && sz[u] > need / 2)
            return find_centroid(u, need, v);
    return v;
}

vector<ll> dfs(int v, int p = -1) {
    vector<ll> res(1);
    res[0] = 1;
    for (int u : g[v]) {
        if (u == p || used[u])
            continue;
        auto now = dfs(u, v);
        now.push_back(0);
        if (SZ(now) > SZ(res))
            swap(now, res);
        for (int i = 0; i < SZ(now); i++) {
            int x = SZ(now) - i - 1;
            res[SZ(res) - x - 1] += now[i];
        }
    }
    return res;
}

void decomposition(int v) {
    calc_sz(v, -1);
    if (sz[v] == 1) {
        return;
    }
    v = find_centroid(v, sz[v], -1);
    vector<ll> have(1, 1);
//    cout << "centroid: " << v + 1 << '\n';
    for (int u : g[v]) {
        if (used[u])
            continue;
        auto now = dfs(u, v);
        reverse(ALL(now));
        now.insert(now.begin(), 0);
//        cout << u + 1 << ": ";
//        for (int x : now)
//            cout << x << ' ';
//        cout << '\n';
        auto mult = fft::multiply(have, now);
        mult.resize(n);
        for (int i = 0; i < SZ(mult); i++)
            ans[i] += mult[i];
        if (SZ(have) < SZ(now))
            swap(now, have);
        for (int i = 0; i < SZ(now); i++)
            have[i] += now[i];
    }
    used[v] = 1;
    for (int u : g[v])
        if (!used[u])
            decomposition(u);
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    decomposition(0);
    for (int i = 1; i < n; i++)
        cout << ans[i] << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("h.in", "r", stdin);
#else
    freopen("tree-paths.in", "r", stdin);
    freopen("tree-paths.out", "w", stdout);
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
